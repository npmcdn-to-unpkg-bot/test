package main

import "flag"
import "fmt"
import "io"
import "os"
import "strconv"
import "bufio"

var infile *string = flag.String("i", "infile", "File contains values for sorting")
var outfile *string = flag.String("o", "outfile", "File to receive sorted values")
var algorithm *string = flag.String("a", "qsort", "Sort algorithm")

func readValues(infile string)(values []int, err error) {
    file, err := os.Open(infile)
    if err != nil {
        fmt.Println("Failed to open the input file", infile)
        return
    }

    defer file.Close()

    br := bufio.NewReader(file)
    values = make([]int, 0)
    for {
        line, isPrefix, err1 := br.ReadLine()
        if err1 != nil {
            if err1 != io.EOF {
                err = err1
            }
            break
        }

        if isPrefix {
            fmt.Println("A too long line, seems unsexpected.")
            return
        }

        str := string(line)
        value, err1 := strconv.Atoi(str)
        if err1 != nil {
            err = err1
            return
        }
        values = append(values, value)
    }
    return
}

func main() {
    flag.Parse()

    if infile != nil {
        fmt.Println("infile = ", *infile, "outfile =", *outfile, "algorithm =", *algorithm)
    }

    values, err := readValues(*infile)
    if err == nil {
        fmt.Println("Read values:", values)
    } else {
        fmt.Println(err)
    }
}