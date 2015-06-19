
/*
dynamic_cast
dynamic_cast can only be used with pointers and references to classes (or with void*).
                 ^^^^              ^^^^^^^^     ^^^^^^^^^^     ^^^^^            ^^^
Its purpose is to ensure that the result of the type conversion points 
to a valid complete object of the destination pointer type.

This naturally includes pointer upcast (converting from pointer-to-derived to pointer-to-base), 
                                ^^^^^
in the same way as allowed as an implicit conversion.
But dynamic_cast can also downcast (convert from pointer-to-base to pointer-to-derived)
                          ^^^^^^^
polymorphic classes (those with virtual members) if -and only if- the pointed object 
is a valid complete object of the target type. For example:
*/


/*
Compatibility note: 
-------------------
This type of dynamic_cast requires Run-Time Type Information (RTTI) to keep track of dynamic types. 
Some compilers support this feature as an option which is disabled by default. 
This needs to be enabled for runtime type checking using dynamic_cast to work properly with these types.

try this:
  g++ dynamic_cast.cpp -fno-rtti
*/

// dynamic_cast
#include <iostream>
#include <exception>
using namespace std;

class Base { virtual void dummy() {} };
class Derived: public Base { int a; };

int main () {
  try {
    Base * pba = new Derived;
    Base * pbb = new Base;
    Derived * pd;
    // void* pv = new char();

    pd = dynamic_cast<Derived*>(pba);
    if (pd==0) cout << "Null pointer on first type-cast.\n";

    pd = dynamic_cast<Derived*>(pbb);
    if (pd==0) cout << "Null pointer on second type-cast.\n";

    // pd = dynamic_cast<Derived>(pv);
    // if (pd==0) cout << "Null pointer on third type-cast.\n";
  } catch (exception& e) {cout << "Exception: " << e.what();}
  return 0;
}