package main

import "fmt"

func pSlice(slice []int) {
    fmt.Println("Slice len=", len(slice), ", cap=", cap(slice), ", Elements:")
    for _, v := range slice {
        fmt.Print(v, " ")
    }
    fmt.Println()
}

func main() {
    var myArray [10]int = [10]int{1,2,3,4,5,6,7,8,9,10}

    var mySlice []int = myArray[:5]
    fmt.Println("Elements of myArray:")
    for _, v := range(myArray) {
        fmt.Print(v, " ")
    }

    fmt.Println("\nElememnts of mySlice:")
    for _, v := range mySlice {
        fmt.Print(v, " ")
    }
    fmt.Println()

    // create
    mySlice1 := make([]int, 5)
    pSlice(mySlice1)
    mySlice2 := make([]int, 5, 10)
    pSlice(mySlice2)
    mySlice3 := []int {1,2,3,4,5,6}
    pSlice(mySlice3)
    mySlice3 = append(mySlice3, -1, -1)
    pSlice(mySlice3)
    mySlice3 = append(mySlice3, mySlice2...)
    pSlice(mySlice3)

    fmt.Println("built-in copy...")
    mySlice4 := []int{1,2,3,4,5}
    mySlice5 := []int{7,8,9}
    pSlice(mySlice4)
    pSlice(mySlice5)
    copy(mySlice4, mySlice5)
    pSlice(mySlice4)
    pSlice(mySlice5)

}