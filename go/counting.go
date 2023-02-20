package main

import (
	"fmt"
	"math/rand"
	"time"
)

const N int = 100
const M int = 299

func counting() {

	var arr [N]int
	rand.Seed(time.Now().Unix())

	for i := 0; i < N; i++ {
		arr[i] = 1 + rand.Int()%M
		fmt.Println(i, " : ", arr[i])
	}

	var count [M + 1]int

	for i := 0; i < N; i++ {
		count[arr[i]]++
	}

	var sorted [N]int

	for i, j := 0, 0; i < M+1; i++ {

		for count[i] != 0 {
			sorted[j] = i
			count[i]--
			j++
		}

	}

	fmt.Printf("sorted: %v\n", sorted)
}
