
#ifndef FOOBAR_FOO_H
#define FOOBAR_FOO_H

// #if defined(_WIN32)
// // #if defined(mylib_EXPORTS)
//   #define MYLIB_EXPORT __declspec( dllexport )
//  // #else
//  //  #define MYLIB_EXPORT __declspec( dllimport )
//  // #endif
// #else
//   #define MYLIB_EXPORT
// #endif

#include <foo/config.h>

// MYLIB_EXPORT 
void foo(void);

#ifdef DAFEI
void dafei();
#endif

#endif
