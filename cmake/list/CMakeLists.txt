cmake_minimum_required(VERSION 2.8)



set(a_list
aaaaa
bbb bbb
ccccc
)

message("a_list is ${a_list}")


set(a_list
aaaaa
"bbb bbb"
ccccc
)

message("a_list is ${a_list}")
