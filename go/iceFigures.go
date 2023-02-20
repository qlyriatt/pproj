package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

func iceFigures() {
	scanner := bufio.NewScanner(os.Stdin)

	scanner.Scan()

	vars := strings.Split(scanner.Text(), " ")
	N, _ := strconv.Atoi(vars[0])
	X, _ := strconv.Atoi(vars[1])
	T, _ := strconv.ParseInt(vars[2], 10, 64)

	_ = N
	scanner.Scan()
	kilos := strings.Split(scanner.Text(), " ")
	delta := make(map[int]int)

	for i, str := range kilos {
		val, _ := strconv.Atoi(str)
		if val-X >= 0 {
			delta[i+1] = val - X
		} else {
			delta[i+1] = X - val
		}
	}

	keys := make([]int, 0, len(delta))
	for k := range delta {
		keys = append(keys, k)
	}

	sort.SliceStable(keys, func(i, j int) bool {
		return delta[keys[i]] < delta[keys[j]]
	})

	result := make([]int, 0)
	for _, key := range keys {
		T -= int64(delta[key])
		if T < 0 {
			break
		}
		result = append(result, key)
	}

	fmt.Println(len(result))
	if len(result) == 0 {
		return
	}
	sort.Ints(result)
	for _, val := range result {
		fmt.Print(val, " ")
	}
}
