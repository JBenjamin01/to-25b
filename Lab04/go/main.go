package main

import (
	"fmt"
	"math"
	"runtime"
	"time"
)

func main() {
	const A = 2.0
	const B = 20.0
	NUM_GOROUTINES := runtime.NumCPU()

	fmt.Println(" GOLANG - Calculadora paralela")
	fmt.Println("=============================")
	fmt.Printf("Funcion a integrar: f(x) = 2x^2 + 3x + 0.5\n")
	fmt.Printf("Limites: [%.1f, %.1f]\n", A, B)
	fmt.Printf("Goroutines a utilizar (nucleos logicos): %d\n", NUM_GOROUTINES)
	fmt.Println("=============================")

	start := time.Now()

	areaAnterior := 0.0
	areaActual := -1.0
	nTrapecios := 1
	const TOLERANCIA = 1e-7

	fmt.Println("\nIniciando convergencia...")
	for math.Abs(areaActual-areaAnterior) > TOLERANCIA {
		areaAnterior = areaActual
		areaActual = calcularIntegralParalelo(miFuncion, A, B, nTrapecios, NUM_GOROUTINES)

		// Usamos '\r' (retorno de carro) para que el cursor vuelva al inicio de la línea
		fmt.Printf("\r -> Iterando... Trapecios: %-10d | Area actual: %.8f", nTrapecios, areaActual)

		nTrapecios *= 2
	}

	duration := time.Since(start)

	fmt.Println()

	fmt.Println("\n//======= RESULTADOS FINALES =======//")
	fmt.Println("Convergencia alcanzada.")
	fmt.Printf("Area final:\t\t%.8f\n", areaActual)
	fmt.Printf("Trapecios necesarios:\t%d\n", nTrapecios/2)
	fmt.Printf("Goroutines concurrentes:\t%d\n", NUM_GOROUTINES)
	fmt.Printf("Tiempo de ejecucion:\t%d ms\n", duration.Milliseconds())
	fmt.Println("//==================================//")
}
