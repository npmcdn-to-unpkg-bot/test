
cmake_minimum_required(VERSION 2.8)


set(a_list
    c++_static
    bbbb
    cccc
    dddd
    eeee
)

message("---------------------------------------")
message("dafei a_list:${a_list}")


function(filter_list src_list_name dst_list_name expr)
    message("dafei src_list_name: ${src_list_name} : ${${src_list_name}}")

    set(a_new_list)
    foreach (item ${${src_list_name}})
        if (item MATCHES ${expr})
            message("match ${expr} :${item}")
        else()
            list(APPEND a_new_list ${item})
            message("dafei item:${item}")
        endif()
    endforeach()
    message("in function a_new_list:${a_new_list}")
    set(${dst_list_name} ${a_new_list} PARENT_SCOPE)
endfunction()

filter_list(a_list new_list "bb")
filter_list(a_list new_list "c.*_static")
message("new list:${new_list}")
message("---------------------------------------")




