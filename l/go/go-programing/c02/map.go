package main

import "fmt"

type PersonInfo struct {
    ID string
    Name string
    Address string
}

func pMap(m map[string] PersonInfo) {
    fmt.Println("Print the map ...")
    for k,v := range m {
        fmt.Println(k, ":", v)
    }
}

func main() {
    var personDB map[string] PersonInfo
    personDB = make(map[string] PersonInfo)
    personDB["12345"] = PersonInfo{"12345", "Tom", "room 203"}
    personDB["1"] = PersonInfo{"1", "Jack", "room 101"}

    person, ok := personDB["1234"]
    if ok {
        fmt.Println("Found person", person.Name, "with ID 1234")
    } else {
        fmt.Println("Did not find person with ID 12345.")
    }

    // traversal
    pMap(personDB)

    // delete
    delete(personDB, "12345")
    pMap(personDB)
}