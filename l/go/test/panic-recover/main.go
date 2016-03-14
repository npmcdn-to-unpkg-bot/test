package main

import (
    "fmt"
)

func main() {
    defer func() { // 必须要先声明defer，否则不能捕获到panic异常
        if err := recover(); err != nil {
            fmt.Println(err)
        } else {
            fmt.Println("No panic")
        }
    }()

    panic("I am a panic")
}