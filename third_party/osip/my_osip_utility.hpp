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

#define LOG_DAFEI() \
        std::cout << "[" << __FILE__ << ":" << __LINE__ <<"] [" << __FUNCTION__ << "] "
#define TO_STRING_ENTRY(x) \
        case x:  \
        s = #x;  \
        break;

// osip utility
std::string event_type_to_string(int type);
std::string kill_transaction_to_string(int type);
std::string transport_error_to_string(int type);
std::string rcv_request_to_string(int type);
std::string message_callback_type_to_string(int type);
std::string transaction_state_to_string(int type);

// MESSAGE HELP FUNCTIONS
int build_response_default (osip_message_t** dest, osip_dialog_t* dialog, int status, osip_message_t* request);
char* build_random_number();
