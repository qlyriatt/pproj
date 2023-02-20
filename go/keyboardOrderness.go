package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func keyboardOrderness() {
	scanner := bufio.NewScanner(os.Stdin)

	scanner.Scan()
	N, _ := strconv.Atoi(scanner.Text())

	keyboard := make(map[int]int, N)

	scanner.Scan()
	var sym []int
	for _, val := range strings.Split(scanner.Text(), " ") {
		val, _ := strconv.Atoi(val)
		sym = append(sym, val)
	}

	scanner.Scan()
	var pos []int
	for _, val := range strings.Split(scanner.Text(), " ") {
		val, _ := strconv.Atoi(val)
		pos = append(pos, val)
	}

	i := 0
	for i < N {
		keyboard[sym[i]] = pos[i]
		i++
	}

	scanner.Scan()
	K, _ := strconv.Atoi(scanner.Text())

	scanner.Scan()
	var text []int
	for _, val := range strings.Split(scanner.Text(), " ") {
		val, _ := strconv.Atoi(val)
		text = append(text, val)
	}

	prev := text[0]
	i = 1
	order := 0
	for i < K {
		if keyboard[text[i]] != keyboard[prev] {
			order++
		}
		prev = text[i]
		i++
	}

	fmt.Print(order)
}
