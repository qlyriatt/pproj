package main

import "fmt"

var bills = [...]int{5000, 2000, 1000, 500, 200, 100, 50, 10, 5, 2, 1}

func main() {

	fmt.Print("Введите сумму заказа, внесенную сумму: ")
	var order, input int
	fmt.Scan(&order, &input) // предполагается, что значения не превышают int64, input > order

	change := input - order
	amounts := make([]int, len(bills))
	for i := range amounts {
		amounts[i] = 0
	}

	for i := 0; change > 0; i++ {
		amount := 0
		for {
			change -= bills[i]
			if change < 0 {
				change += bills[i]
				break
			}
			amount++
		}
		amounts[i] = amount
	}

	for i, val := range amounts {
		if val == 0 {
			continue
		}
		fmt.Printf("%v руб.: %v шт.\n", bills[i], val)
	}
}
