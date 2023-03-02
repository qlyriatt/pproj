package main

import (
	"fmt"
	"log"
	"sort"
)

func getSortedView(m map[int]int) []int {

	keys := make([]int, 0, len(m))
	for k := range m {
		keys = append(keys, k)
	}

	sort.SliceStable(keys, func(i, j int) bool {
		return (m)[keys[i]] > (m)[keys[j]]
	})

	return keys
}

const PRINT_WITH_TYPES = true // true выводит количество вместе с типами линз, false только количество

type order struct {
	lense    int
	quantity int
}

func main() {

	fmt.Print("Введите N: ")
	var n int
	fmt.Scanln(&n)
	if n <= 0 {
		fmt.Println("Неверное N")
		return
	}

	fmt.Print("Введите массив чисел: ")
	lenses := make([]int, n)
	for i := range lenses {
		fmt.Scan(&lenses[i])
	}

	// map[линза]количество
	opt := make(map[int]int)
	for _, val := range lenses {
		opt[val]++
	}

	// сортировка по убыванию для map
	sorted := getSortedView(opt)
	log.Println(sorted)
	var orders []order
	// подбираем пары, начиная с самых распространенных
	buy := 0
	for _, key := range sorted {

		log.Println(key, " : ", opt[key])
		if PRINT_WITH_TYPES {
			buy = 0
		}

		// убираем пары линз для одинаковых запросов lenses
		for opt[key] > 1 {
			opt[key] -= 2
			buy++
			if PRINT_WITH_TYPES && opt[key] == 0 {
				orders = append(orders, order{key, buy})
			}
		}

		if opt[key] == 1 { // ищем +-1 для линзы без пары
			buy++
			opt[key]--
			if PRINT_WITH_TYPES {
				orders = append(orders, order{key, buy})
			}
			val, ok := opt[key-1] // -1
			if ok && val > 0 {
				opt[key-1]--
				continue
			}
			val, ok = opt[key+1] // +1
			if ok && val > 0 {
				opt[key+1]--
				continue
			}
		}
	}

	// вывод
	if PRINT_WITH_TYPES {
		for _, val := range orders {
			fmt.Printf("%v : %v шт.\n", val.lense, val.quantity)
		}
	} else {
		fmt.Println("Buy: ", buy)
	}
}
