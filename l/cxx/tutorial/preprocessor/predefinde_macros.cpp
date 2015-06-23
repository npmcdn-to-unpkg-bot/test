#include <iostream>

int main() {
/*
The following macro names are always defined (they all begin and end with two underscore characters, _):

 macro   value
----------------------------------------------
__LINE__        Integer value representing the current line in the source code file being compiled.
__FILE__        A string literal containing the presumed name of the source file being compiled.
__DATE__        A string literal in the form "Mmm dd yyyy" containing the date in which the compilation process began.
__TIME__        A string literal in the form "hh:mm:ss" containing the time at which the compilation process began.
__cplusplus     An integer value. All C++ compilers have this constant defined to some value. Its value depends on the version of the standard supported by the compiler:
                199711L: ISO C++ 1998/2003
                201103L: ISO C++ 2011
                Non conforming compilers define this constant as some value at most five digits long. Note that many compilers are not fully conforming and thus will have this constant defined as neither of the values above.
__STD_HOSTED__  1 if the implementation is a hosted implementation (with all standard headers available) 0 otherwise.
*/

std::cout << "__FILE__ " <<  __FILE__ << std::endl;
std::cout << "__LINE__ " <<  __LINE__ << std::endl;
std::cout << "__DATE__ " <<  __DATE__ << std::endl;
std::cout << "__TIME__ " <<  __TIME__ << std::endl;
std::cout << "__cplusplus " << __cplusplus << std::endl;
// std::cout << "__STD_HOSTED "<< __STD_HOSTED__ << std::endl;



/*
The following macros are optionally defined, generally depending on whether a feature is available:

macro   value
----------------------------------------------------------------------
__STDC__                            In C: if defined to 1, the implementation conforms to the C standard.
                                    In C++: Implementation defined.
__STDC_VERSION__                    In C:
                                    199401L: ISO C 1990, Ammendment 1
                                    199901L: ISO C 1999
                                    201112L: ISO C 2011
                                    In C++: Implementation defined.
__STDC_MB_MIGHT_NEQ_WC__            1 if multibyte encoding might give a character a different value in character literals
__STDC_ISO_10646__                  A value in the form yyyymmL, specifying the date of the Unicode standard followed by the encoding of wchar_t characters
__STDCPP_STRICT_POINTER_SAFETY__    1 if the implementation has strict pointer safety (see get_pointer_safety)
__STDCPP_THREADS__                  1 if the program can have more than one thread

*/
}