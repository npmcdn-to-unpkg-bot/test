#include <iostream>


#if TABLE_SIZE>200
#undef TABLE_SIZE
#define TABLE_SIZE 200
 
#elif TABLE_SIZE<50
#undef TABLE_SIZE
#define TABLE_SIZE 50
 
#else
#undef TABLE_SIZE
#define TABLE_SIZE 100
#endif
 
using namespace std;
int main() {

    int table[TABLE_SIZE]; 

    // # and ##
    // # make anything to a string
    #define str(x) #x
    cout << str(test) << std::endl;
    // the operator ## concatenates two arguments leaving no blank spaces between them:
    #define glue(a,b) a ## b
    glue(c,out) << "test" << std::endl;

}