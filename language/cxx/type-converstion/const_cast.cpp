/*

const_cast
This type of casting manipulates the constness of the object pointed by a pointer,
either to be set or to be removed. For example, in order to pass a const pointer
to a function that expects a non-const argument:

*/

// const_cast
#include <iostream>
using namespace std;

void print (char * str)
{
  cout << str << '\n';
}

int main () {
  const char * c = "sample text";
  print ( const_cast<char *> (c) );
  return 0;
}
sample text
Edit & Run
