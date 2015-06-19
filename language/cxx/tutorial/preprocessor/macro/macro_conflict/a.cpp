#include "test1.hpp"
#undef DAFEI // This will not conflict with test2.hpp DAFEI.
#include "test2.hpp"

// test1.hpp has #define DAFEI 123
// test2.hpp has class named DAFEI
// We can undef DAFEI after test1.hpp and before test2.hpp


int main() {
    p();
    DAFEI d;
    d.p();
}