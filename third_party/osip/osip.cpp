#define ENABLE_TRACE
#include "my_osip_utility.hpp"
#include <sys/time.h> // Need before osip.h.
#include <osip2/osip.h>
#include <osip2/osip_mt.h>
#include <osip2/osip_dialog.h>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <vector>
#include <iomanip>

static int g_socket_fd = -1;
static int g_send_fd = -1;
static int g_recv_fd = -1;
static int g_wakeup_send_fd = -1;
static int g_wakeup_recv_fd = -1;
static osip_t* g_osip = NULL;
static std::vector<osip_dialog_t*> g_dialogs;
osip_transaction_t* g_out_transaction = NULL;
osip_transaction_t* g_inc_transaction = NULL;

static const size_t BUFFSIZE = 1600;  // MTU usually doesn't exceed 1600
static const unsigned MESSAGE_ENTRY_MAX_LENGTH = 256;
static const unsigned MAX_ADDR_STR = 128;

static bool g_begin_log = false;



void exit_if_failed(int ret, const std::string& info);
void cleanup_socket();

// All Callbacks
// This function, which is implementation of transportation ourself, is used to send message.
int cb_send_message(osip_transaction_t* tr, osip_message_t* sip, char *host, int port, int out_socket);

void cb_xixt_kill_transaction(int type, osip_transaction_t* tr);

void cb_transport_error(int type, osip_transaction_t* tr, int error);

void cb_rcv1xx(int type, osip_transaction_t* tr, osip_message_t* sip);
void cb_rcv2xx(int type, osip_transaction_t* tr, osip_message_t* sip);
void cb_rcv3456xx(int type, osip_transaction_t* tr, osip_message_t* sip);

void cb_rcvreq(int type, osip_transaction_t* tr, osip_message_t* sip);

// handle incomming message
int handle_incoming_message(const char* buf, size_t len);
void process_new_request(osip_t* osip, osip_event_t* evt);
void process_rcv_cancel(osip_transaction_t* tran, osip_message_t* sip);
void process_ict_rcv_2xx(osip_transaction_t* tr, osip_message_t* sip);
void process_bye(osip_transaction_t* tran, osip_message_t* sip);

int send_invite();
osip_dialog_t* search_existing_dialog(osip_message_t* sip);
void add_existing_dialog(osip_dialog_t* dialog);


// main usage and net, command thread.
void usage(const char* process);
int init_net(bool as_server);
void* command_fun(void* arg);
void wakeup_select();

int main(int argc, char** argv){
    if (argc != 2) {
        usage(argv[0]);
        return 0;
    }

    bool as_server = false;
    if ( 0 == strcmp(argv[1], "true")) {
        as_server = true;
    } else if (0 != strcmp(argv[1], "false")) {
        usage(argv[0]);
        return 0;
    }

    // Init net
    assert(init_net(as_server) == 0);

    // Init command thread.
    pthread_t th_command;
    int ret = pthread_create(&th_command, NULL, command_fun, NULL);
    exit_if_failed(ret, "Failed to create thread");

    // Init osip
    osip_t* osip = NULL;
    ret = osip_init(&osip);
    exit_if_failed(ret, "Failed to init osip");
    g_osip = osip;

    // set callbacks.
    // callback called when a SIP message must be sent.
    osip_set_cb_send_message(osip, &cb_send_message);
    // callback called when a SIP transaction is TERMINATED.
    osip_set_kill_transaction_callback(osip ,OSIP_ICT_KILL_TRANSACTION, &cb_xixt_kill_transaction);
    osip_set_kill_transaction_callback(osip ,OSIP_IST_KILL_TRANSACTION, &cb_xixt_kill_transaction);
    osip_set_kill_transaction_callback(osip ,OSIP_NICT_KILL_TRANSACTION, &cb_xixt_kill_transaction);
    osip_set_kill_transaction_callback(osip ,OSIP_NIST_KILL_TRANSACTION, &cb_xixt_kill_transaction);
    //callback called when the callback to send message have failed.
    osip_set_transport_error_callback(osip ,OSIP_ICT_TRANSPORT_ERROR, &cb_transport_error);
    osip_set_transport_error_callback(osip ,OSIP_IST_TRANSPORT_ERROR, &cb_transport_error);
    osip_set_transport_error_callback(osip ,OSIP_NICT_TRANSPORT_ERROR, &cb_transport_error);
    osip_set_transport_error_callback(osip ,OSIP_NIST_TRANSPORT_ERROR, &cb_transport_error);
    // callback called when a received answer has been accepted by the transaction.
    osip_set_message_callback(osip ,OSIP_ICT_STATUS_1XX_RECEIVED, &cb_rcv1xx);
    osip_set_message_callback(osip ,OSIP_ICT_STATUS_2XX_RECEIVED, &cb_rcv2xx);
    osip_set_message_callback(osip ,OSIP_ICT_STATUS_3XX_RECEIVED, &cb_rcv3456xx);
    osip_set_message_callback(osip ,OSIP_ICT_STATUS_4XX_RECEIVED, &cb_rcv3456xx);
    osip_set_message_callback(osip ,OSIP_ICT_STATUS_5XX_RECEIVED, &cb_rcv3456xx);
    osip_set_message_callback(osip ,OSIP_ICT_STATUS_6XX_RECEIVED, &cb_rcv3456xx);
    // callback called when a received answer has been accepted by the transaction.
    osip_set_message_callback(osip ,OSIP_NICT_STATUS_1XX_RECEIVED, &cb_rcv1xx);
    osip_set_message_callback(osip ,OSIP_NICT_STATUS_2XX_RECEIVED, &cb_rcv2xx);
    osip_set_message_callback(osip ,OSIP_NICT_STATUS_3XX_RECEIVED, &cb_rcv3456xx);
    osip_set_message_callback(osip ,OSIP_NICT_STATUS_4XX_RECEIVED, &cb_rcv3456xx);
    osip_set_message_callback(osip ,OSIP_NICT_STATUS_5XX_RECEIVED, &cb_rcv3456xx);
    osip_set_message_callback(osip ,OSIP_NICT_STATUS_6XX_RECEIVED, &cb_rcv3456xx);
    // callback called when a received request has been accepted by the transaction.
    osip_set_message_callback(osip ,OSIP_IST_INVITE_RECEIVED,       &cb_rcvreq);
    osip_set_message_callback(osip ,OSIP_IST_INVITE_RECEIVED_AGAIN, &cb_rcvreq);
    osip_set_message_callback(osip ,OSIP_IST_ACK_RECEIVED,          &cb_rcvreq);
    osip_set_message_callback(osip ,OSIP_IST_ACK_RECEIVED_AGAIN,    &cb_rcvreq);
    osip_set_message_callback(osip ,OSIP_NIST_REGISTER_RECEIVED,    &cb_rcvreq);
    osip_set_message_callback(osip ,OSIP_NIST_BYE_RECEIVED,         &cb_rcvreq);
    osip_set_message_callback(osip ,OSIP_NIST_CANCEL_RECEIVED,      &cb_rcvreq);
    osip_set_message_callback(osip ,OSIP_NIST_INFO_RECEIVED,        &cb_rcvreq);
    osip_set_message_callback(osip ,OSIP_NIST_OPTIONS_RECEIVED,     &cb_rcvreq);
    osip_set_message_callback(osip ,OSIP_NIST_SUBSCRIBE_RECEIVED,   &cb_rcvreq);
    osip_set_message_callback(osip ,OSIP_NIST_NOTIFY_RECEIVED,      &cb_rcvreq);
    osip_set_message_callback(osip ,OSIP_NIST_UNKNOWN_REQUEST_RECEIVED, &cb_rcvreq);

    // setup transport layer.
    // osip_thread_create(0, transport_fun, osip);

    fd_set read_fds;
    char buffer[BUFFSIZE] = { 0 };
    struct timeval timeout = {0, 0};

    while (true) {
        // std::cout << "loop start ....." << std::endl;
        FD_ZERO(&read_fds);
        FD_SET(g_recv_fd, &read_fds);
        FD_SET(g_wakeup_recv_fd, &read_fds);
        int maxfd = g_recv_fd + 1;

        switch(select(maxfd, &read_fds, NULL, NULL, &timeout)) {
        case -1:
            std::cout << "select error" << std::endl;
            exit(-1);
            break;
        case 0:
            break;
        default:
            {
                // This is where we receive sip messages when fd is ready to read.
                if (FD_ISSET(g_recv_fd, &read_fds)) {
                    int len = read(g_recv_fd, buffer, BUFFSIZE);
                    if (len == -1) {
                        std::cout << "read error" << std::endl;
                        exit(-1);
                    }
                    buffer[len] = 0;
                    handle_incoming_message(buffer, len);
                } else if (FD_ISSET(g_wakeup_recv_fd, &read_fds)) {
                    std::cout << "this is a wakeup" << std::endl;
                    int len = read(g_wakeup_recv_fd, buffer, BUFFSIZE);
                    buffer[len] = 0;
                    // assert(strcmp(buffer, "a") == 0);
                    // Wake up select for our outgoing message handling.
                } else {
                    assert(false);
                }

            }
            break;
        }

        if (g_inc_transaction) {
            LOG_DAFEI() << "execute Before report IST status" << std::endl
                    << "         state:" << transaction_state_to_string(g_inc_transaction->state) << std::endl;
        }
        
        osip_ict_execute(osip);
        osip_ist_execute(osip);
        osip_nict_execute(osip);
        osip_nist_execute(osip);
        osip_timers_ict_execute(osip);
        osip_timers_ist_execute(osip);
        osip_timers_nict_execute(osip);
        osip_timers_nist_execute(osip);

        if (g_inc_transaction) {
            LOG_DAFEI() << "execute After report IST status" << std::endl
                    << "state:" << transaction_state_to_string(g_inc_transaction->state) << std::endl;
        }

        // Get minimal timeout to wake up us. Put them behind execute is the best way.
        // This is perfect to handle Real Time.
        osip_timers_gettimeout(osip, &timeout);
        LOG_DAFEI() << " secs:" << timeout.tv_sec << ", usecs:" << timeout.tv_usec << std::endl;
    }

    pthread_join(th_command, NULL);
    
    cleanup_socket();
    return 0;
} // main


void usage(const char* process)
{
    std::cout << process << " true/false\n" 
            << "  true  socket server. listen on localhost:7890\n"
            << "  false socket client. try to connect localhost:7890\n" << std::endl;
}

int init_net(bool as_server)
{
    if (as_server) {
        std::cout << "This is server" << std::endl;
    } else {
        std::cout << "This is client" << std::endl;
    }

    // Init pipe for wakeup select.
    int pipe_fds[2];
    if (pipe(pipe_fds) != 0) {
        std::cout << "pipe failed" << std::endl;
        exit(-1);
    }
    g_wakeup_recv_fd = pipe_fds[0]; // 0 receive
    g_wakeup_send_fd = pipe_fds[1]; // 1 send

    // Init socket
    unsigned short port = 7890;
    const char* ip = "127.0.0.1";

    if (as_server) {
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        if(-1 == fd) {
            printf("socket fail ! \n");
            return -1;
        }
        g_socket_fd = fd;

        struct sockaddr_in s_add, c_add;
        bzero(&s_add,sizeof(struct sockaddr_in));
        s_add.sin_family = AF_INET;
        s_add.sin_addr.s_addr = htonl(INADDR_ANY);
        s_add.sin_port = htons(port);

        if(-1 == bind(fd, (struct sockaddr *)(&s_add), sizeof(struct sockaddr))) {
            printf("bind fail !\n");
            return -1;
        }

        if(-1 == listen(fd, 2)) {
            printf("listen fail !\n");
            cleanup_socket();
            return -1;
        }
        printf("listen ok\n");

        socklen_t sin_size = sizeof(struct sockaddr);
        for (int i=0; i<2; i++) {
            int l_fd = accept(fd, (struct sockaddr *)(&c_add), &sin_size);
            if(-1 == l_fd) {
                printf("accept fail !\n");
                cleanup_socket();
                return -1;
            }
            printf("accept ok! fd=%d, from %s:%d\n",l_fd, inet_ntoa(c_add.sin_addr), ntohs(c_add.sin_port));
            if (i==0)
                g_recv_fd = l_fd; // server use the first fd as receive fd, client use it as send fd.
            else
                g_send_fd = l_fd;
        }

        return 0;
    }

    // as client
    struct sockaddr_in add;
    bzero(&add,sizeof(struct sockaddr_in));
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = inet_addr(ip);
    add.sin_port = htons(port);

    for (int i = 0; i < 2; i++) {
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        if(-1 == fd) {
            printf("socket fail ! \n");
            return -1;
        }

        if(-1 == connect(fd,(struct sockaddr *)(&add), sizeof(struct sockaddr))) {
            printf("connect fail! error:%s\n", strerror(errno));
            cleanup_socket();
            return -1;
        }
        printf("connect ok !\n");

        if (i==0) {
            g_send_fd = fd;
        } else {
            g_recv_fd = fd;
        }
    }

    return 0;
}

int handle_incoming_message(const char* buffer, size_t len)
{
    std::string log_msg(buffer, len);
    LOG_DAFEI() << "message received:\n---------------" << log_msg << "\n--------------" << std::endl;

    osip_event_t *evt = osip_parse(buffer, len);
    if (evt == NULL) {
        std::cout << "osip_parse failed:--------\n" << log_msg << std::endl;
        return -1;
    }

    // char *msg;
    // size_t msgLen;
    // int ret = osip_message_to_str(evt->sip, &msg, &msgLen);
    // if (ret != 0) {
    //     std::cout << "Cannot get printable msg:";
    //     return -1;
    // }

    // LOG_DAFEI() << "new event created\n"
    //         << "type:" << event_type_to_string(evt->type) << "\n"
    //         // << "transactionid:" << evt->transactionid << "\n" // Here must be 0. Because we havn't find transaction for this event.
    //         << "sip:" << msg << std::endl;;
    // osip_free(msg);

    // use "branch" to identity transaction for this event.
    int rc = osip_find_transaction_and_add_event(g_osip, evt);
    if(0 != rc) {
        // should free event.
        LOG_DAFEI() << "this event has no transaction, create a new one." << std::endl;
        if (MSG_IS_REQUEST(evt->sip)) {
            LOG_DAFEI() << "process_new_request, event type:" << event_type_to_string(evt->type) << std::endl;
            process_new_request(g_osip, evt);
        } else if (MSG_IS_RESPONSE(evt->sip)) {
            LOG_DAFEI() << "process_response_out_of_transacation" << std::endl;
            // process_response_out_of_transacation(g_osip, evt);
        }
    } else {
        LOG_DAFEI() << "Find transaction for this event" << std::endl;
        // Already add event, wakeup select.
        wakeup_select();
    }

    return 0;
}

int send_invite()
{
    static int g_seq_num = 1;
    char* seq_num_str = NULL;
    char temp[MESSAGE_ENTRY_MAX_LENGTH] = { 0 };
    char sip_port[MESSAGE_ENTRY_MAX_LENGTH] = { 0 };
    char expires[10];

    osip_call_id_t* call_id_ptr;
    osip_cseq_t* cseq_ptr;
    osip_message_t* invite_msg;

    int status = osip_message_init(&invite_msg);
    if (status != 0) {
        std::cout << "osip message init failed" << std::endl;
        return -1;
    }
    
    osip_message_set_method(invite_msg, osip_strdup("INVITE"));
    osip_uri_init(&(invite_msg->req_uri));
    if ((status = osip_uri_parse(invite_msg->req_uri, "sip:10.10.10.1")) != 0) {
        std::cout << "osip uri parse failed" << std::endl;
        osip_message_free(invite_msg);
        return -1;
    }

    osip_message_set_version(invite_msg, osip_strdup("SIP/2.0"));
    osip_message_set_status_code(invite_msg, 0); // 0 is request not response
    osip_message_set_reason_phrase(invite_msg, NULL);

    osip_message_set_to(invite_msg, "sip:Hal@10.10.10.2");
    osip_message_set_from(invite_msg, "sip:dafei@10.10.10.3");
    osip_from_set_tag(invite_msg->from, build_random_number());

    if ((status = osip_call_id_init(&call_id_ptr)) != 0) {
        std::cout << "call id failed" << std::endl;
        osip_message_free(invite_msg);
        return -1;
    }

    char* call_id_number_str = (char*)osip_malloc(MAX_ADDR_STR);
    unsigned number = osip_build_random_number();
    sprintf(call_id_number_str, "%u", number);
    osip_call_id_set_number(call_id_ptr, call_id_number_str);

    osip_call_id_set_host(call_id_ptr, osip_strdup("10.1.1.63"));

    invite_msg->call_id = call_id_ptr;

    if ((status = osip_cseq_init(&cseq_ptr)) != 0) {
        osip_message_free(invite_msg);
        return -1;
    }

    seq_num_str = (char*)osip_malloc(MAX_ADDR_STR);
    sprintf(seq_num_str, "%i", g_seq_num++);
    osip_cseq_set_number(cseq_ptr, seq_num_str);
    osip_cseq_set_method(cseq_ptr, osip_strdup("INVITE"));
    invite_msg->cseq = cseq_ptr;

    osip_message_set_max_forwards(invite_msg, "70");
    // UDP will set time a, TCP won't. But they all have time-b.
    // Use udp or tcp to represent reliable or unreliable transport layer that we use.
    sprintf(temp, "SIP/2.0/%s %s;branch=z9hG4bK%u", "UDP", "10.10.10.3", osip_build_random_number());
    osip_message_set_via(invite_msg, temp);

    osip_message_set_contact(invite_msg, "dafei@10.10.10.3");
    sprintf(expires, "%i", 3600);
    osip_message_set_expires(invite_msg, expires);

    osip_message_set_content_length(invite_msg, "0");
    osip_message_set_user_agent(invite_msg, "TotalView 1.0");

    osip_transaction_t* transaction;
    osip_event_t* event;
    if ((status = osip_transaction_init(&transaction, ICT, g_osip, invite_msg)) != 0) {
        std::cout << "Failed to init transportation :" << status << std::endl;
        return -1; 
    }
    osip_transaction_set_your_instance(transaction, g_osip);// store osip in transaction for later usage.


    if ((event = osip_new_outgoing_sipmessage(invite_msg)) == NULL) {
        std::cout << "Can't allocate message" << std::endl;
        osip_message_free(invite_msg);
        return -1;
    }

    event->transactionid = transaction->transactionid;

    if((status = osip_message_force_update(invite_msg)) != 0){
        std::cout << "Failed force update:" << status << std::endl;
        osip_message_free(invite_msg);
        return -1;
    }

    if((status = osip_transaction_add_event(transaction, event)) != 0){
        std::cout << "Can't add event" << std::endl;
        osip_message_free(invite_msg);
        return -1;
    }

    wakeup_select();

    g_out_transaction = transaction;
    return 0;
}

void wakeup_select()
{
    int ret = write(g_wakeup_send_fd, "a", 1); // wake up select
    if (ret != 1) {
        std::cout << "wakeup failed" << std::endl;
        exit(-1);
    }
}

int send_cancel()
{
    if (!g_out_transaction) {
        LOG_DAFEI() << "No out transaction at all" << std::endl;
        return -1;
    }

    if (!MSG_IS_STATUS_1XX(g_out_transaction->last_response)) {
        LOG_DAFEI() << "transaction last_response is not 1xx" << std::endl;
        return -1;
    }

    int i;
    osip_message_t *request;
    osip_message_t* request_cancelled = g_out_transaction->orig_request;
    
    i = osip_message_init (&request);
    if (i != 0) {
        LOG_DAFEI() << "failed to init message" << std::endl;
        return i;
    }
    
    /* prepare the request-line */
    osip_message_set_method (request, osip_strdup ("CANCEL"));
    osip_message_set_version (request, osip_strdup ("SIP/2.0"));
    osip_message_set_status_code (request, 0);
    osip_message_set_reason_phrase (request, NULL);
    
    i = osip_uri_clone (request_cancelled->req_uri, &(request->req_uri));
    if (i != 0) {
      osip_message_free (request);
      request = NULL;
      LOG_DAFEI() << "failed to clone message uri" << std::endl;
      return i;
    }
    
    i = osip_to_clone (request_cancelled->to, &(request->to));
    if (i != 0) {
      osip_message_free (request);
      request = NULL;
      LOG_DAFEI() << "failed to clone message to" << std::endl;
      return i;
    }
    i = osip_from_clone (request_cancelled->from, &(request->from));
    if (i != 0) {
      osip_message_free (request);
      request = NULL;
      LOG_DAFEI() << "failed to clone message from" << std::endl;
      return i;
    }
    
    /* set the cseq and call_id header */
    i = osip_call_id_clone (request_cancelled->call_id, &(request->call_id));
    if (i != 0) {
      osip_message_free (request);
      request = NULL;
      LOG_DAFEI() << "failed to clone message call_id" << std::endl;
      return i;
    }
    i = osip_cseq_clone (request_cancelled->cseq, &(request->cseq));
    if (i != 0) {
      osip_message_free (request);
      request = NULL;
      LOG_DAFEI() << "failed to clone message cseq" << std::endl;
      return i;
    }
    osip_free (request->cseq->method);
    request->cseq->method = osip_strdup ("CANCEL");
    if (request->cseq->method == NULL) {
      osip_message_free (request);
      request = NULL;
      LOG_DAFEI() << "failed set cancel method" << std::endl;
      return OSIP_NOMEM;
    }
    
    /* copy ONLY the top most Via Field (this method is also used by proxy) */
    {
      osip_via_t *via;
      osip_via_t *via2;
    
      i = osip_message_get_via (request_cancelled, 0, &via);
      if (i < 0) {
        osip_message_free (request);
        request = NULL;
        LOG_DAFEI() << "failed to get via" << std::endl;
        return i;
      }
      i = osip_via_clone (via, &via2);
      if (i != 0) {
        osip_message_free (request);
        request = NULL;
        LOG_DAFEI() << "failed to clone via" << std::endl;
        return i;
      }
      osip_list_add (&request->vias, via2, -1);
    }
    
    /* add the same route-set than in the previous request */
    {
      int pos = 0;
      osip_route_t *route;
      osip_route_t *route2;
    
      while (!osip_list_eol (&request_cancelled->routes, pos)) {
        route = (osip_route_t *) osip_list_get (&request_cancelled->routes, pos);
        i = osip_route_clone (route, &route2);
        if (i != 0) {
          osip_message_free (request);
          request = NULL;
          LOG_DAFEI() << "failed to clone route" << std::endl;
          return i;
        }
        osip_list_add (&request->routes, route2, -1);
        pos++;
      }
    }
    
    osip_message_set_max_forwards (request, "70");        /* a UA should start a request with 70 */
    osip_message_set_user_agent (request, osip_strdup("Webview 0.1"));

    // Send it.
    osip_transaction_t* transaction = NULL;
    int r = osip_transaction_init(&transaction, NICT, g_osip, request);
    if (r != 0) {
        LOG_DAFEI() << "transacation init failed" << std::endl;
        return -1;
    }

    osip_event_t* sipevent = osip_new_outgoing_sipmessage (request);
    sipevent->transactionid = transaction->transactionid;

    r = osip_transaction_add_event (transaction, sipevent);
    if (r !=0) {
        LOG_DAFEI()  << "Failed to add event" << std::endl;
        return r;
    }
    LOG_DAFEI() << "success to add cancel event" << std::endl;

    wakeup_select();

  return 0;
}

void send_bye()
{
    // TODO we only have one dialog right now
    if (g_dialogs.size() ==0) {
        LOG_DAFEI() << "This is no dialog" << std::endl;
        return;
    }

    osip_dialog_t* dialog = g_dialogs[0];

    osip_message_t* bye;
    int i = build_request_within_dialog(&bye, "BYE", dialog);
    if (i !=0) {
        LOG_DAFEI() << "Failed to create bye" << std::endl;
        return;
    }

    char *msg;
    size_t msgLen;
    i = osip_message_to_str(bye, &msg, &msgLen);
    if (i != 0 ) {
        LOG_DAFEI() << "Failed to to str" << std::endl;
    } else {
        LOG_DAFEI() << "bye message is :\n"
            << std::string(msg, msgLen) << std::endl;
        free(msg);
    }

    // Create transation
    osip_transaction_t* transaction = NULL;
    int r = osip_transaction_init(&transaction, NICT, g_osip, bye);
    if (r != 0) {
        LOG_DAFEI() << "transacation init failed" << std::endl;
        return;
    }

    osip_event_t* sipevent = osip_new_outgoing_sipmessage (bye);
    sipevent->transactionid = transaction->transactionid;

    r = osip_transaction_add_event (transaction, sipevent);
    if (r !=0) {
        LOG_DAFEI()  << "Failed to add event" << std::endl;
        return;
    }

    wakeup_select();

}

void send_ok()
{
    if (!g_inc_transaction) {
        LOG_DAFEI() << "no in transaction" << std::endl;
        return;
    }

    // Send ok will kill this IST.
    // re-send 200 is TU's responsibilty, not transport. Unlike others.

    osip_message_t *answer;
    // We build 200 use dialog's to_tag which is created when we send 180.
    osip_dialog_t* dialog = g_dialogs[0];
    assert(dialog);
    int r = build_response_default(&answer, dialog, 200, g_inc_transaction->orig_request);
    if (r != 0) {
        LOG_DAFEI() << "Failed to build_response_default" << std::endl;
        return;
    }
    osip_message_set_content_length(answer, "0");

    osip_event_t* evt_answer = osip_new_outgoing_sipmessage(answer);
    evt_answer->transactionid = g_inc_transaction->transactionid;

    osip_transaction_add_event(g_inc_transaction, evt_answer);

    wakeup_select();
}

void send_ack(osip_transaction_t* transaction, osip_message_t* sip)
{
    osip_dialog_t* dialog = NULL;
    int index = 0;
    for (; index < g_dialogs.size(); index++) {
        if (0 == osip_dialog_match_as_uac(g_dialogs[index], sip)) {
            dialog = g_dialogs[index];
            break;
        }
    }

    if (!dialog) {
        LOG_DAFEI() << "didn't find the dialog" << std::endl;
        // Should return 48? to tell remote that we didn't find one.
        return;
    }

    osip_message_t* answer;
    int i = build_request_within_dialog(&answer, "ACK", dialog);
    if (i !=0) {
        LOG_DAFEI() << "Failed to create ACK" << std::endl;
        return;
    }

    char *msg;
    size_t msgLen;
    i = osip_message_to_str(answer, &msg, &msgLen);
    if (i != 0 ) {
        LOG_DAFEI() << "Failed to to str" << std::endl;
    } else {
        LOG_DAFEI() << "answer message is :\n"
            << std::string(msg, msgLen) << std::endl;
        free(msg);
    }

    osip_event_t* sipevent = osip_new_outgoing_sipmessage (answer);
    sipevent->transactionid = transaction->transactionid;

    i = osip_transaction_add_event (transaction, sipevent);
    if (i !=0) {
        LOG_DAFEI()  << "Failed to add event" << std::endl;
        return;
    }

    wakeup_select();
}

void* command_fun(void* arg)
{
    std::cout << "command thread is running" << std::endl;
    std::string command;
    std::cout << ">";
    while (std::getline(std::cin, command)) {
        if (command == "invite") {
            assert(g_osip);
            send_invite();
        } else if (command == "cancel") {
            send_cancel();
        } else if (command == "bye") {
            send_bye();
        } else if (command == "ok") {
            send_ok();
        } else {
            std::cout << "unknown command:" << command << std::endl;
        }

        std::cout << ">" << std::flush;
    }
    return NULL;
}


void exit_if_failed(int ret, const std::string& info) {
    if (ret != 0) {
        std::cout << "exit_if_failed:" << ret << " ," << info << std::endl;
        exit(-1);
    }
}

void cleanup_socket() {
    std::cout << "cleanup socket" << std::endl;
    if (g_socket_fd > 0) {
        close(g_socket_fd);
        g_socket_fd = -1;
    }
    if (g_send_fd > 0) {
        close(g_send_fd);
        g_send_fd = -1;
    }
}

void process_new_request(osip_t* osip, osip_event_t* evt)
{
    // see how exosip process new request in  _eXosip_process_newrequest ()
    int ctx_type;
    if (MSG_IS_INVITE(evt->sip)) {
        LOG_DAFEI() << "this is IST event" << std::endl;
        ctx_type = IST;
    } else if (MSG_IS_ACK(evt->sip)) {
        ctx_type = -1;
    } else if (MSG_IS_REQUEST(evt->sip)) {
        LOG_DAFEI() << "This is NIST event" << std::endl;
        ctx_type = NIST;
    } else {
        ctx_type = -1;
        osip_event_free(evt);
        LOG_DAFEI() << "This is not a new request event, free and return" << std::endl;
        return;
    }

    osip_transaction_t* transaction = NULL;
    if (ctx_type != -1) {
        int r = osip_transaction_init(&transaction, (osip_fsm_type_t)ctx_type, osip, evt->sip);
        if (r != 0) {
            osip_event_free(evt);
            LOG_DAFEI() << "transacation init failed" << std::endl;
            return;
        }
        evt->transactionid = transaction->transactionid;
        osip_transaction_set_your_instance(transaction, osip); // store osip in transaction for later usage.
        r = osip_transaction_add_event(transaction, evt);
        if (r !=0) {
            LOG_DAFEI()  << "Failed to add event" << std::endl;
            return;
        }
        // STORE IST transaction only.
        if (transaction->ctx_type == IST) {
            LOG_DAFEI() << "This is an IST (INVITE) incoming transaction, store it" << std::endl;
            g_inc_transaction = transaction;
        }
    }

    if (ctx_type == IST) {
        osip_message_t *answer;
        int r = build_response_default(&answer, NULL, 100, evt->sip);
        if (r != 0) {
            osip_transaction_free(transaction);
            return;
        }
        osip_message_set_content_length (answer, "0");

        osip_event_t* evt_answer = osip_new_outgoing_sipmessage (answer);
        evt_answer->transactionid = transaction->transactionid;

        r = osip_transaction_add_event(transaction, evt_answer);
        if (r !=0) {
            LOG_DAFEI()  << "Failed to add event" << std::endl;
            return;
        }

        sleep(1);
        // TODO dafei in order to received the message one bye one.
        // or 100 and 180 will received the same time in TCP.
        // TODO maybe change it to UDP.    
    }
}

#define MATCH_CHECK(x);  \
    if (!x) { \
        LOG_DAFEI() << #x << " is null";   \
        return -1;  \
    }

int match_invite(osip_transaction_t* invite, osip_message_t* cancel)
{
    osip_generic_param_t *br = NULL;
    osip_generic_param_t *br2 = NULL;
    osip_via_t *via;
    osip_via_param_get_byname (invite->topvia, "branch", &br);
    MATCH_CHECK(br);
    via = (osip_via_t*)osip_list_get (&cancel->vias, 0);
    MATCH_CHECK(via);
    osip_via_param_get_byname (via, "branch", &br2);
    MATCH_CHECK(br2);

    MATCH_CHECK(br->gvalue);
    MATCH_CHECK(br2->gvalue);
    if (0 != strcmp(br->gvalue, br2->gvalue)) {
        std::string v1(br->gvalue, strlen(br->gvalue));
        std::string v2(br2->gvalue, strlen(br2->gvalue));
        LOG_DAFEI() << "v1:[" << v1 << "], v2:[" << v2 << "]not match" << std::endl;
        return -1;
    }

    // if ((0 != osip_call_id_match (invite->callid, cancel->call_id)) ||
    //         (0 != osip_to_tag_match (invite->to, cancel->to)) &||
    //         (0 != osip_from_tag_match (invite->from, cancel->from)) ||
    //         (0 != osip_via_match (invite->topvia, via))) {
    //  // From may have no tag right now.
    //     return -1;
    // }

    // Match OK.
    return 0;
}

void process_rcv_cancel(osip_transaction_t* tr, osip_message_t* sip)
{
    // First, we need to handle cancel transaction and response with a 200 ok or 481
    // find no match invite.
    // Then, we need to find the INVITE transaction and answer with 487.(canceled)

    int cancel_status = 200; // default 200 ok for cancel.
    // Find the INVITE in incoming transacton
    if (!g_inc_transaction) {
        LOG_DAFEI() << "Have no incoming transaction at all?" << std::endl;
    } else {
        // match the invite
        if (0 == match_invite(tr, sip)) {
            if (g_inc_transaction->state == IST_TERMINATED ||
                    g_inc_transaction->state == IST_CONFIRMED ||
                    g_inc_transaction->state == IST_COMPLETED) {
                LOG_DAFEI() << "match INVITE in wrong state." << std::endl;
                cancel_status = 481;
            }  else {
                // We should answer with 487. We answer after answer CANCEL.
            }
        } else {
            LOG_DAFEI() << "NO matach invite for this CANCEL" << std::endl;
            cancel_status = 481; // Not found for this cancel.
        }
    }

    // For CANCEL trasaction, reponse with 200 ok.
    LOG_DAFEI() << "Response CANCEL with " << cancel_status << std::endl;
    osip_message_t *answer;
    int r = build_response_default(&answer, NULL, cancel_status, sip);
    if (r != 0) {
        LOG_DAFEI()  << "Failed to build_response_default" << std::endl;
        osip_transaction_free(tr); // dafei Is this right????
        return;
    }
    osip_message_set_content_length(answer, "0");

    osip_event_t* evt_answer = osip_new_outgoing_sipmessage(answer);
    if (!evt_answer) {
        LOG_DAFEI()  << "Failed to osip_new_outgoing_sipmessage" << std::endl;
        return;
    }
    evt_answer->transactionid = tr->transactionid;

    r = osip_transaction_add_event(tr, evt_answer);
    if (r !=0) {
        LOG_DAFEI()  << "Failed to add event" << std::endl;
        return;
    }

    // ANSWER INVITE with 487
    while (cancel_status == 200) {
        LOG_DAFEI() << "Response INVITE with " << 487 << std::endl;
        osip_message_t *invite_answer;
        int r = build_response_default(&invite_answer, NULL, 487, g_inc_transaction->orig_request);
        if (r != 0) {
            LOG_DAFEI()  << "Failed to build_response_default" << std::endl;
            break;
        }
        osip_message_set_content_length(invite_answer, "0");

        osip_event_t* evt_invite_answer = osip_new_outgoing_sipmessage(invite_answer);
        if (!evt_invite_answer) {
            LOG_DAFEI()  << "Failed to osip_new_outgoing_sipmessage" << std::endl;
            break;
        }
        evt_invite_answer->transactionid = g_inc_transaction->transactionid;

        r = osip_transaction_add_event(g_inc_transaction, evt_invite_answer);
        if (r !=0) {
            LOG_DAFEI()  << "Failed to add event" << std::endl;
            break;
        }
        break;
    }
    
    wakeup_select();
}

void process_bye(osip_transaction_t* transaction, osip_message_t* sip)
{
    // First to match the dialog
    osip_dialog_t* dialog = NULL;
    int index = 0;
    for (; index < g_dialogs.size(); index++) {
        if (0 == osip_dialog_match_as_uas(g_dialogs[index], sip)) {
            dialog = g_dialogs[index];
            break;
        }
    }

    if (!dialog) {
        LOG_DAFEI() << "No match dialog for this bye" << std::endl;
        // Should build a 48? to tell we didn't found.
        return;
    }

    // Check if we have an old BYE transaction if have, return

    // 
    osip_message_t* answer;
    int r = build_response_default(&answer, dialog, 200, sip);
    if (r != 0 ) {
        LOG_DAFEI() << "build answer failed" << std::endl;
        return;
    }

    osip_message_set_content_length(answer, "0");

    osip_event_t* evt_answer = osip_new_outgoing_sipmessage (answer);
    evt_answer->transactionid = transaction->transactionid;

    r = osip_transaction_add_event (transaction, evt_answer);
    if (r != 0) {
        LOG_DAFEI() << "Failed to add event" << std::endl;
        osip_message_free(answer);
        return;
    }

    // Release the dialog now.
    osip_dialog_free(dialog);
    g_dialogs.erase(g_dialogs.begin() + index);

    wakeup_select();
}

void process_ict_rcv_2xx(osip_transaction_t* tr, osip_message_t* sip)
{
    // This handles ICT receiving 2xx
    if (MSG_TEST_CODE(sip, 200)) {
        // This is 200. We need to send ACK.
        // TODO dafei
        send_ack(tr, sip);
    }
}

int cb_send_message(osip_transaction_t* tr, osip_message_t* sip, char *host, int port, int out_socket)
{
    char *msg;
    size_t msgLen;
    int ret = osip_message_to_str(sip, &msg, &msgLen);
    if (ret != 0) {
        std::cout << "Cannot get printable msg:";
        return -1;
    }
    
    // // check time.
    // static timeval store_time = {0, 0};
    // struct timeval now;
    // gettimeofday(&now, NULL);
    // int msec = 0;
    // if (!(store_time.tv_sec == 0 && store_time.tv_usec == 0)) {
    //     msec = (now.tv_sec - store_time.tv_sec)*1000 + (now.tv_usec - store_time.tv_usec)/1000;
    // }
    // memcpy(&store_time, &now, sizeof(struct timeval));
    // std::cout << "time msec:" << msec << std::endl;

    if (tr->ctx_type == IST && MSG_IS_RESPONSE_FOR(sip, "INVITE")
        && MSG_TEST_CODE(sip, 200)) {
        LOG_DAFEI() << "This is a 200 for INVITE, should re-send until we get ACK" << std::endl;
    }

    int r = write(g_send_fd, msg, msgLen);
    if (r == -1) {
        return -1;
    }
    // return non OSIP_SUCCESS( 0 ) will lead to callback cb_transport_error();
    // return value is the int error in cb_transport_error( ..., int error);
    return OSIP_SUCCESS;
}

void cb_xixt_kill_transaction(int type, osip_transaction_t* tr)
{
    LOG_DAFEI() << kill_transaction_to_string(type) << ", transactionid=" << tr->transactionid << std::endl;

    if (g_out_transaction == tr) {
        g_out_transaction = NULL;
    }
    if (g_inc_transaction == tr) {
        g_inc_transaction = NULL;
    }

    // TODO maybe we should check the INT transaction if it's killed properly.

    // Need to remove transacation here.
    // This will free the transaction.
    int i = osip_remove_transaction(g_osip, tr);
    if (i != 0) {
        std::cout << "osip_remove_transacation failed:" << i
                << ", transactionid=" << tr->transactionid << std::endl;
    }

}

void cb_transport_error(int type, osip_transaction_t* tr, int error)
{
    LOG_DAFEI() << transport_error_to_string(type) << ": tr->transactionid:" << tr->transactionid
            << ", error:" << error << std::endl;
    // error is what we return in cb_send_message.
    // When transport encouter error,
    // first, cb_transport_error is called.
    // second, cb_xixt_kill_transaction is called.
}

osip_dialog_t* search_existing_dialog(osip_message_t* sip)
{
    for (int i=0; i< g_dialogs.size(); i++) {
        if (osip_dialog_match_as_uac(g_dialogs[i], sip)) {
            return g_dialogs[i];
        }
        if (osip_dialog_match_as_uas(g_dialogs[i], sip)) {
            return g_dialogs[i];
        }
    }

    LOG_DAFEI() << "match no dialog" << std::endl;
    return NULL;
}

void add_existing_dialog(osip_dialog_t* dialog)
{
    g_dialogs.push_back(dialog);
}

void cb_rcv1xx(int type, osip_transaction_t* tr, osip_message_t* sip)
{
    LOG_DAFEI() << "receive " << std::setfill('0') << std::setw(3) << sip->status_code << std::endl;
    osip_dialog_t* dialog;
    if (MSG_IS_RESPONSE_FOR(sip, "INVITE") && !MSG_TEST_CODE(sip, 100)) { // osip said between 101 and 199 to setup a dialog
        dialog = search_existing_dialog(sip);
        if (!dialog) {
            int i = osip_dialog_init_as_uac(&dialog, sip);
            if (i != 0) {
                LOG_DAFEI() << "Failed to create a dialog" << std::endl;
            } else {
                add_existing_dialog(dialog);
            }
        } else {
            // we match a dialog, then what ?
            LOG_DAFEI() << "match the dialog" << std::endl;
        }
    }
    // other request doesn't establish dialog.
}

void cb_rcv2xx(int type, osip_transaction_t* tr, osip_message_t* sip)
{
    LOG_DAFEI() << "receive " << std::setfill('0') << std::setw(3) << sip->status_code
            << ", " << message_callback_type_to_string(type) << std::endl;
    if (MSG_IS_RESPONSE_FOR(sip, "INVITE")) {
        LOG_DAFEI() << "msg is response for INVITE" << std::endl;
        process_ict_rcv_2xx(tr, sip);
        return;
    }

    if (MSG_IS_RESPONSE_FOR(sip, "BYE")) {
        LOG_DAFEI() << "msg is response for BYE" << std::endl;
    } else if (MSG_IS_RESPONSE_FOR(sip, "CANCEL")) {
        LOG_DAFEI() << "msg is response for CANCEL" << std::endl;
    } else {
        std::string method(sip->cseq->method);
        LOG_DAFEI() << "msg is response for " << method << "We didn't handle this" << std::endl;
    }

}

void cb_rcv3456xx(int type, osip_transaction_t* tr, osip_message_t* sip)
{
    LOG_DAFEI() << "receive " << std::setfill('0') << std::setw(3) << sip->status_code << std::endl;
}


void cb_rcvreq(int type, osip_transaction_t* transaction, osip_message_t* sip)
{
    // char *msg;
    // size_t msgLen;
    // int ret = osip_message_to_str(sip, &msg, &msgLen);
    // if (ret != 0) {
    //     std::cout << "Cannot get printable msg:";
    // }

    // LOG_DAFEI() << message_callback_type_to_string(type) << "\n" 
    //         << "tr->transactionid=" << tr->transactionid
    //         << "\nmsg:------------\n" << msg << "\n--------------" << std::endl;

    LOG_DAFEI() << message_callback_type_to_string(type)  << ", tr->transactionid=" << transaction->transactionid << std::endl;
    switch (type) {
    case OSIP_IST_INVITE_RECEIVED:
        {
            // Let's return 180 ring here. IST will create dialog with this response
            // ICT will create dialog when receive 180.
            osip_message_t *answer;
            int r = build_response_default(&answer, NULL, 180, sip);
            if (r != 0) {
                osip_transaction_free(transaction);
                break;
            }
            osip_message_set_content_length (answer, "0");


            // create dialog here.
            osip_dialog_t* dialog = NULL;
            r = osip_dialog_init_as_uas(&dialog, sip, answer);
            if (r != 0) {
                LOG_DAFEI() << "Failed to create dialog" << std::endl;
            } else {
                add_existing_dialog(dialog);
            }

            // Send back.
            osip_event_t* evt_answer = osip_new_outgoing_sipmessage (answer);
            evt_answer->transactionid = transaction->transactionid;

            r = osip_transaction_add_event(transaction, evt_answer);
            if (r !=0) {
                LOG_DAFEI()  << "Failed to add event" << std::endl;
                break;
            }
        }
        break;
    case OSIP_NIST_CANCEL_RECEIVED:
        process_rcv_cancel(transaction, sip);
        break;
    case OSIP_NIST_BYE_RECEIVED:
        process_bye(transaction, sip);
    default:
        break;
    }
}