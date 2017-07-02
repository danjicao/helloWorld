package main


import (
    "fmt"
    "os"
)


//
// Usage: go run helloWorld.go argv_1 argv_2
//


func main() {
    fmt.Println(">>  arguments:")
    argc := len(os.Args)
    fmt.Fprintf(os.Stdout, "    argc=%d\n", argc)
    for i := 0; i < argc; i++ {
		fmt.Fprintf(os.Stdout, "    argv[%d]=%s\n", i, os.Args[i])
	}

    fmt.Println(">>  Appliction Begin")
	fmt.Println("Hello, World!\n")
    fmt.Println(">>  Appliction End")

    os.Exit(0)
}

