#include <iostream>

/*
Implicit conversion
-------------------------------------------

Implicit conversions are automatically performed when a value is copied to a compatible type. For example:

short a=2000;
int b;
b=a;


Here, the value of a is promoted from short to int without the need of any explicit operator.
This is known as a standard conversion. Standard conversions affect fundamental data types, 
and allow the conversions between numerical types (short to int, int to float, double to int...), 
to or from bool, and some pointer conversions.

Converting to int from some smaller integer type, or to double from float is known as promotion, and is guaranteed to produce the exact same value in the destination type. Other conversions between arithmetic types may not always be able to represent the same value exactly:
If a negative integer value is converted to an unsigned type, the resulting value corresponds to its 2's complement bitwise representation (i.e., -1 becomes the largest value representable by the type, -2 the second largest, ...).
The conversions from/to bool consider false equivalent to zero (for numeric types) and to null pointer (for pointer types); true is equivalent to all other values and is converted to the equivalent of 1.
If the conversion is from a floating-point type to an integer type, the value is truncated (the decimal part is removed). If the result lies outside the range of representable values by the type, the conversion causes undefined behavior.
Otherwise, if the conversion is between numeric types of the same kind (integer-to-integer or floating-to-floating), the conversion is valid, but the value is implementation-specific (and may not be portable).

Some of these conversions may imply a loss of precision, which the compiler can signal with a warning. This warning can be avoided with an explicit conversion.

For non-fundamental types, 
arrays and functions implicitly convert to pointers, 
and pointers in general allow the following conversions:
    - Null pointers can be converted to pointers of any type
    - Pointers to any type can be converted to void pointers.
    - Pointer upcast: pointers to a derived class can be converted to a pointer of an accessible and unambiguous base class,
        without modifying its const or volatile qualification.

*/


/*
Implicit conversions with classes
-----------------------------------------------

In the world of classes, implicit conversions can be controlled by means of three member functions:
    - Single-argument constructors: allow implicit conversion from a particular type to initialize an object.
    - Assignment operator:  allow implicit conversion from a particular type on assignments.
    - Type-cast operator:  allow implicit conversion to a particular type.
*/


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
