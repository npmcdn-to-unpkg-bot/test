/*
static_cast
static_cast can perform conversions between pointers to related classes, 
not only upcasts (from pointer-to-derived to pointer-to-base), 
         ^^^^^^^
but also downcasts (from pointer-to-base to pointer-to-derived).
         ^^^^^^^^
No checks are performed during runtime to guarantee that the object being converted is in fact 
a full object of the destination type. Therefore, it is up to the programmer to ensure that the 
conversion is safe. On the other side, it does not incur the overhead of the type-safety checks 
of dynamic_cast.

class Base {};
class Derived: public Base {};
Base * a = new Base;
Derived * b = static_cast<Derived*>(a);


This would be valid code, although b would point to an incomplete object of the class and could lead to runtime errors if dereferenced.

Therefore, static_cast is able to perform with pointers to classes not only the conversions allowed implicitly, but also their opposite conversions.

static_cast is also able to perform all conversions allowed implicitly (not only those with pointers to classes), 
                                    ^^^  ^^^^^^^^            ^^^^        ^^^^^^
and is also able to perform the opposite of these. It can:
    Convert from void* to any pointer type.
        In this case, it guarantees that if the void* value was obtained by converting from that same pointer type, the resulting pointer value is the same.
    Convert integers, floating-point values and enum types to enum types.

Additionally, static_cast can also perform the following:
    - Explicitly call a single-argument constructor or a conversion operator.
    - Convert to rvalue references.
    - Convert enum class values into integers or floating-point values.
    - Convert any type to void, evaluating and discarding the value.
*/


// g++ --std=c++11 static_cast.cpp


#include <iostream>
#include <exception>
using namespace std;

class Base {
public:
    virtual void dummy() {
        cout << "Base dummy\n";
    } 
};
class Derived: public Base {
public:
    Derived() : a(10) {}
    void dummy() {
        cout << "Derived dummy\n";
    }

    void no_value_changed() {
        cout << "no value changed\n";
    }

    void value_changed() {
        cout << "value changed\n";
        a = 10;
    }
    int value() {
        return a;
    }
private:
    int a;
};

enum class SIZE_INT : int {
    BIG = 2,
    SMALL
};

enum class SIZE_CHAR : char {
    BIG = 'a',
    SMALL
};

int main () {
  try {
    Base * pba = new Derived;
    Base * pbb = new Base;
    Base * pbc = new Derived;
    Derived * pd1;
    Derived * pd2;

    pd1 = static_cast<Derived*>(pba);
    if (pd1==0) cout << "Null pointer on first type-cast.\n";
    cout << "value=" << pd1->value() << std::endl;
    pd1->dummy();
    pd1->no_value_changed();
    pd1->value_changed();
    cout << "value=" << pd1->value() << std::endl;
    delete pd1;

    cout << "-----------------------------\n";
    pd2 = static_cast<Derived*>(pbb);
    if (pd2==0) cout << "Null pointer on second type-cast.\n";
    cout << "value=" << pd2->value() << std::endl;  // out of band operation, dangerous
    pd2->dummy();
    pd2->no_value_changed();
    pd2->value_changed();       // // out of band operation, dangerous
    cout << "value=" << pd2->value() << std::endl; // out of band operation, dangerous
    delete pd2;

  } catch (exception& e) {cout << "Exception: " << e.what();}

  cout << "-----------------------------\n";
  // enum class
  int size_int_big = static_cast<int>(SIZE_INT::BIG);
  cout << "SIZE_INT::BIG = " << size_int_big << std::endl;

  char size_char_big = static_cast<char>(SIZE_CHAR::BIG);
  cout << "SIZE_CHAR::BIG = " << size_char_big << std::endl;

  return 0;
}
