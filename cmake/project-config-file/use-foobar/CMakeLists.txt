add_executable(use main.c)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    "${CMAKE_PREFIX_PATH}/CMake/" )

#include_directories(${CMAKE_PREFIX_PATH}/include)
#link_directories(${CMAKE_PREFIX_PATH}/lib)
#set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${CMAKE_PREFIX_PATH}/lib)

find_package(FooBar REQUIRED)
if (FooBar_FOUND)
message("dafei FooBar found")
message("dafei FOOBAR_LIBRARIES is :${FOOBAR_LIBRARIES}")
message("dafei FOOBAR_INCLUDE_DIRS is :${FOOBAR_INCLUDE_DIRS}")
message("dafei FOOBAR_EXECUTABLE is :${FOOBAR_EXECUTABLE}")

include_directories(${FOOBAR_INCLUDE_DIRS})
else()
message("dafei not found FooBar")
endif()


get_target_property(tmp foo COMPILE_DEFINITIONS)
message("dafei get_target_property COMPILE_DEFINITIONS:${tmp}")


get_target_property(tmp foo PUBLIC_HEADER)
message("dafei get_target_property PUBLIC_HEADER:${tmp}")
# WHY ?????? NOT FOUND ?????

target_link_libraries(use ${FOOBAR_LIBRARIES})
