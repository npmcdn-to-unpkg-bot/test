package main

import (
    "fmt"
    "time"
)
// 传递参数-ldflags "-s"，忽略debug的打印信息
// 传递-gcflags "-N -l" 参数，这样可以忽略Go内部做的一些优化，
// 聚合变量和函数等优化，这样对于GDB调试来说非常困难，
// 所以在编译的时候加入这两个参数避免这些优化。

// go build -gcflags "-N -l" gdbfile.go

func counting(c chan<- int) {
    for i := 0; i < 10; i++ {
        time.Sleep(2 * time.Second)
        c <- i
    }
    close(c)
}

func main() {
    msg := "Starting main"
    fmt.Println(msg)
    bus := make(chan int)
    msg = "starting a gofunc"
    go counting(bus)
    for count := range bus {
        fmt.Println("count:", count)
    }
}