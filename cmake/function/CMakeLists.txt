cmake_minimum_required(VERSION 2.8)



project(ArgumentExpansion)



function (argument_tester arg)
    message('-------------------------------')
    message(STATUS "ARGN: ${ARGN}")
    message(STATUS "ARGC: ${ARGC}")
    message(STATUS "ARGV: ${ARGV}")
    message(STATUS "ARGV0: ${ARGV0}")
    message(STATUS "ARGV1: ${ARGV1}")

    list(LENGTH ARGV  argv_len)
    message(STATUS "length of ARGV: ${argv_len}")
    set(i 0)
    while( i LESS ${argv_len})
         list(GET ARGV ${i} argv_value)
         message(STATUS "argv${i}: ${argv_value}")

         math(EXPR i "${i} + 1")
    endwhile()


endfunction ()

argument_tester(arg0 arg1 arg2 arg3)
set(l1
0
0)
set(l1 
1
2)
set(l2
3
4)
set(l3
4
5)
argument_tester(l0 l1 l2 l3)

function(tester2 arg1 arg2)
    message("--------------------------")
    message("arg1 is ${arg1}: (${${arg1}})")
    message("arg2 is ${arg2}: (${${arg2}})")
endfunction()
tester2(l1 l2)

    message("--------------------------")

function(twice varName)
  SET(${varName} ${${varName}}${${varName}} PARENT_SCOPE)
endfunction()

SET(arg "foo")
twice(arg)
MESSAGE(STATUS ${arg})