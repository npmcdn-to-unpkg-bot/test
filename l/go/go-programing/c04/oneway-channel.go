package main

import "fmt"
import "time"

func main() {
    ch1 := make(chan int)
    // chR := <-chan int(ch1)
    // chW := chan<- int(ch1)

    go func (ch chan<- int) {
        fmt.Println("Producer starts to work...")
        for i := 0; i<5; i++ {
            time.Sleep(1)
            fmt.Println("Produce one data")
            ch <- i
        }
        close(ch)
    }(ch1)

    for {
        d, ok := <-ch1
        if !ok {
            fmt.Println("Received error")
            break
        } else {
            fmt.Println("Received data", d)
        }
    }
}