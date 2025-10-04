package main

import "math"

type Funcion func(float64) float64

// Implementación concreta de f(x) = 2x^2 + 3x + 0.5 que está en el lab
func miFuncion(x float64) float64 {
	return 2*math.Pow(x, 2) + 3*x + 0.5
}
