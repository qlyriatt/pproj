package main

import (
	"fmt"
	"math/big"
)

func main() {

	fmt.Print("Введите N: ")
	var input string
	fmt.Scan(&input)

	// программа работает для всех 0 <= X < 2^64
	var test big.Int
	test.SetString(input, 10)
	if !test.IsUint64() {
		fmt.Println("X is too big")
		return
	}

	x := test.Uint64()

	var sum big.Int
	sum.SetUint64(0)

	var n = uint64(0)
	var tmp big.Int
	for n <= x {
		tmp.SetUint64(n)
		if tmp.ProbablyPrime(5) { // функция имеет стопроцентную точность для всех чисел < 2^64
			sum.Add(&sum, &tmp)
		}
		n++
	}

	fmt.Println("Sum: ", sum.String())
}
