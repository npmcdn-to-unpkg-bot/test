#include <iostream>

// Usage:
// #line number "filename"


int main() {

#line 88 "a_replaced_filename"
int a?;

}

// $ g++ line-control.cpp 
// a_replaced_filename: In function ‘int main()’:
// a_replaced_filename:88:6: error: expected initializer before ‘?’ token
//  ^                   ^
//  |                   |
//  see                 see
