package main

import "fmt"

func MyPrintf(args ...interface{}) {
    for _, arg := range args {
        switch arg.(type) {
        case int:
            fmt.Println(arg, "is an int")
        case string:
            fmt.Println(arg, "is a string")
        case int64:
            fmt.Println(arg, "is an int64")
        default:
            fmt.Println(arg, "is an unkown type")
        }
    }
}

func main() {
    var v1 int = 1
    var v2 int64 = 234
    var v3 string = "hello"
    var v4 float32 = 1.234
    MyPrintf(v1, v2, v3, v4)
}