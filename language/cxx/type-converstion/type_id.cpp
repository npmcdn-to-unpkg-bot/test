/*
typeid
typeid allows to check the type of an expression: 

typeid (expression)

This operator returns a reference to a constant object of type type_info that is defined
 in the standard header <typeinfo>. A value returned by typeid can be compared with another 
 value returned by typeid using operators == and != or can serve to obtain a null-terminated 
 character sequence representing the data type or class name by using its name() member.

*/
/*
When typeid is applied to classes, typeid uses the RTTI to keep track of the type of dynamic objects. 
                                                   ^^^^
When typeid is applied to an expression whose type is a polymorphic class, 
the result is the type of the most derived complete object:
*/

/*
  -----------------------------------
  g++ type_id.cpp [ -frtti ]
  try this: g++ type_id.cpp -fno-rtti

  ./a.out  | c++filt -t
  Or it's undemangling name
*/

// typeid
#include <iostream>
#include <typeinfo>
#include <exception>
using namespace std;

int main () {
  int * a,b;
  a=0; b=0;
  if (typeid(a) != typeid(b))
  {
    cout << "a and b are of different types:\n";   // a and b are of different types:
    cout << "a is: " << typeid(a).name() << '\n';  // a is: int *
    cout << "b is: " << typeid(b).name() << '\n';  // b is: int  
  }

// typeid, polymorphic class

class Base { virtual void f(){} };
class Derived : public Base {};

  try {
    Base* a = new Base;
    Base* b = new Derived;
    cout << "a is: " << typeid(a).name() << '\n';   // a is: class Base *
    cout << "b is: " << typeid(b).name() << '\n';   // b is: class Base *
    cout << "*a is: " << typeid(*a).name() << '\n'; // *a is: class Base
    cout << "*b is: " << typeid(*b).name() << '\n'; // *b is: class Derived
  } catch (exception& e) { cout << "Exception: " << e.what() << '\n'; }
  return 0;
}


// a is: class Base *
// b is: class Base *
// *a is: class Base
// *b is: class Derived