package main

import (
    "fmt"
    "runtime"
)

func main() {
    fmt.Println("NumCPU", runtime.NumCPU())
    fmt.Println("NumGoroutine", runtime.NumGoroutine())
    fmt.Println("precious GOMAXPROCS", runtime.GOMAXPROCS(10))
    fmt.Println("precious GOMAXPROCS", runtime.GOMAXPROCS(3))
    fmt.Println("precious GOMAXPROCS", runtime.GOMAXPROCS(8))
}