package main

import "fmt"

// 可见
type Rect struct {
    x, y float64
    width, height float64
}

// 可见
func (r *Rect) Area() float64 {
    return r.width * r.height
}

// 包内可见
func (r Rect) p() {
    fmt.Println("x:", r.x, "y:", r.y, "width:", r.width, "height:", r.height)
}

func main() {
    // init 未进行显式初始化的变量都会被初始化为该类型的零值,例如 bool 类型的零值为 false , int 类型的零值为0, string 类型的零值为空字符串
    r1 := new(Rect)
    r1.p()
    r2 := &Rect{}
    r2.p()
    r3 := &Rect{0, 0, 100, 200}
    r3.p()
    r4 := &Rect{x:22, height:200}
    r4.p()
}