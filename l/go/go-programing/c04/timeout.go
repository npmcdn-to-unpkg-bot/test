package main

import "time"
import "fmt"

func main() {
    ch := make(chan int)
    timeout := make(chan bool, 1)
    go func() {
        time.Sleep(1e9)
        timeout <- true
    }()

    select {
    case <-ch:
        fmt.Println("Receive data from ch")
    case <-timeout:
        fmt.Println("Receive data from timeout")
    }

    go func() {
        ch <- 1
    }()

    select {
    case <-ch:
        fmt.Println("Receive data from ch")
    case <-timeout:
        fmt.Println("Receive data from timeout")
    }
}