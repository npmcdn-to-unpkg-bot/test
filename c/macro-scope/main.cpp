#include "a.h"
#include "b.h"

int main() {

#ifdef DAFEI
# pragma message "in main, dafei is defined"
#else
# pragma message "in main, dafei is undefined"
#endif

#ifdef XIAOFEI
# pragma message "in main, XIAOFEI is defined"
#else
# pragma message "in main, XIAOFEI is undefined"
#endif
}