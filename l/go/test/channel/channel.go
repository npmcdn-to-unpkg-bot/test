package main

import (
    "fmt"
    "time"
)

func sum(a []int, result chan int) {
    fmt.Println("Start to sum...")
    time.Sleep(3*time.Second)
    total := 0
    for _, v := range a {
        total += v
    }
    fmt.Println("Finished sum...")
    result <- total
}

func main() {
    a := []int{7, 2, 8, -9, 4, 0}
    result := make(chan int)

    go sum(a[:len(a)/2], result)
    go sum(a[len(a)/2:], result)

    fmt.Println("Waiting for result...")
    x, y :=<-result, <-result
    // x,y随机的不一定是哪个结果先来
    fmt.Println("x", x, ", y", y)
}