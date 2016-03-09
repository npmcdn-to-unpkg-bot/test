package main

import "fmt"
import "syscall"

type PathError struct {
    Op string
    Path string
    Err error
}

func (e *PathError)Error() string {
    return e.Op + " " + e.Path + ": " + e.Err.Error()
}

func GotError(name string)(newName string, err error) {
    return name, &PathError{"got", name, err}
}

func main() {
    fi, err := os.
}