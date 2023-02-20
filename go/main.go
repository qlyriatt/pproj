package main

import (
	"fmt"
	"os"
)

func main() {
	if len(os.Args) == 1 {
		fmt.Println("Pass some arguments to start a program")
		return
	}

	for _, val := range os.Args[1:] {
		switch val {
		case "-c":
			counting()
		case "-i":
			iceFigures()
		case "-k":
			keyboardOrderness()
		case "-t":
			trades()
		default:
			fmt.Printf("%v is not a recognised argument\n", val)
		}
	}

}
