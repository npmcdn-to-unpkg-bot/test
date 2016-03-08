package main

import "fmt"

func main() {
    var array = [10] int {1,2,3,4,5,6,7}
    for i := 0; i<len(array); i++ {
        fmt.Println("array[", i, "]=", array[i])
    }
    fmt.Printf("Use range....\n")
    for i, v := range(array) {
        fmt.Println("array[", i, "]=", v)
    }
}