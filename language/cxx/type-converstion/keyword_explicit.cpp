


// implicit conversion of classes:
/*

#include <iostream>
using namespace std;

class A {};

class B {
public:
  // conversion from A (constructor):
  B (const A& x) {}
  // conversion from A (assignment):
  B& operator= (const A& x) {return *this;}
  // conversion to A (type-cast operator)
  operator A() {return A();}
};

int main ()
{
  A foo;
  B bar = foo;    // calls constructor
  bar = foo;      // calls assignment
  foo = bar;      // calls type-cast operator
  return 0;
}
*/

/*
Keyword explicit
On a function call, C++ allows one implicit conversion to happen for each argument. 
This may be somewhat problematic for classes, because it is not always what is intended. 
For example, if we add the following function to the last example:

 
void fn (B arg) {}


This function takes an argument of type B, but it could as well be called with an object of type A as argument:

 
fn (foo);


This may or may not be what was intended. But, in any case, i
t can be prevented by marking the affected constructor with the explicit keyword:
*/

// explicit:
#include <iostream>
using namespace std;

class A {};

class B {
public:
  explicit B (const A& x) {}
  B& operator= (const A& x) {return *this;}
  operator A() {return A();}
};

void fn (B x) {}

int main ()
{
  A foo;
  B bar (foo);
  bar = foo;
  foo = bar;
  
  //  fn (foo);  // not allowed for explicit ctor.
  fn (bar);  

  return 0;
}