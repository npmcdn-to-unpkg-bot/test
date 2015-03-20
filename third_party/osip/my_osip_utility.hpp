#include <sys/time.h> // Need before osip.h.
#include <osip2/osip.h>
#include <osip2/osip_mt.h>
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
std::string to_string(int type);
std::string kill_transaction_to_string(int type);
std::string transport_error_to_string(int type);
std::string rcv_request_to_string(int type);
std::string message_callback_type_to_string(int type);

