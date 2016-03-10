package main

import "fmt"
import "./visiblity"

func main() {
    v1 := visiblity.See{"I'm lowwer", "I'm upper"}
    // fmt.Println(v1.lowwer) // cimpile error
    fmt.Println(v1.Upper)

    // v2 := visiblity.noSee{} // cimpile error
}