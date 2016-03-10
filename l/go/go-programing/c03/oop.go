package main

import "fmt"

// 匿名组合
type Base struct {
    Name string
}

func (base *Base) Foo() {
    fmt.Println("From Base Foo()")
}

func (base *Base) Bar() {
    fmt.Println("From Base Bar()")
}

type Foo struct {
    Base // *Base 你还可以以指针方式从一个类型“派生
    Age int32
    Name string
    // *Base
}

func (foo *Foo) Bar() {
    foo.Base.Bar()
    fmt.Println("From Foo Bar()")
}

func main() {
    v1 := &Foo{Base{"Tom"}, 32, "Lily"}
    v1.Bar()
    v1.Foo()
    fmt.Println("v1.Name is", v1.Name) // Lily
}