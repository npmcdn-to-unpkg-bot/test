package main

import (
    "fmt"
    "time"
)

// ch := make(chan type, number)

// number == 0 ! 无缓冲（阻塞）
// number > 0 ! 缓冲（非阻塞，直到 number 个元素）

func main() {
    c := make(chan int, 2)
    c <- 1
    c <- 2
    // c <- 3 //fatal error: all goroutines are asleep - deadlock!

    fmt.Println(<-c)
    fmt.Println(<-c)


    // test 2
    c1 := make(chan int, 10)
    go send(15, c1)
    for i := range c1 {
        time.Sleep(1*time.Second)
        fmt.Println("get data", i)
    }
}

func send(n int, c chan int) {
    for i := 0; i<n; i++ {
        fmt.Println("Put", i, "into the channel")
        c <- i
    }
    fmt.Println("Close the channel")
    // 记住应该在生产者的地方关闭channel，而不是消费的地方去关闭它，这样容易引起panic
    // 另外记住一点的就是channel不像文件之类的，不需要经常去关闭，只有当你确实没有任何发送数据了，或者你想显式的结束range循环之类的
    close(c)
}