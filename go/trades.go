package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type trade struct {
	buy   int
	sell  int
	delta int
}

func trades() {
	scanner := bufio.NewScanner(os.Stdin)

	scanner.Scan()
	N, _ := strconv.Atoi(scanner.Text())
	scanner.Scan()
	p := strings.Split(scanner.Text(), " ")

	var points []int
	for _, str := range p {
		val, _ := strconv.Atoi(str)
		points = append(points, val)
	}

	var trades []trade
	var min, max int
	for i := 1; i < N; i++ {
		if points[i] > points[i-1] {
			min = i - 1
			max = i
			i++
			for i < N {
				if points[i] <= points[max] {
					break
				}
				max = i
				i++
			}
			trades = append(trades, trade{min, max, points[max] - points[min]})
		}
	}

	fmt.Print(trades)
}
