package main

import "sync"

// worker aquí es la goroutine que calcula una porción de la integral
func worker(limiteInf, limiteSup, h float64, f Funcion, wg *sync.WaitGroup, resultados chan<- float64) {
	defer wg.Done() // Avisa que ha terminado antes de salir

	areaLocal := 0.0
	xActual := limiteInf
	for xActual < limiteSup {
		y1 := f(xActual)
		y2 := f(xActual + h)
		areaLocal += calcularAreaTrapecio(y1, y2, h)
		xActual += h
	}
	resultados <- areaLocal // Resultado parcial para el canal
}

// Con esta función dividimos el trabajo para poder distribuirlo a las goroutines
func calcularIntegralParalelo(f Funcion, a, b float64, nTrapecios, numGoroutines int) float64 {
	var wg sync.WaitGroup
	resultados := make(chan float64, numGoroutines)

	h := (b - a) / float64(nTrapecios)
	intervaloPorGoroutine := (b - a) / float64(numGoroutines)

	for i := 0; i < numGoroutines; i++ {
		limiteInf := a + float64(i)*intervaloPorGoroutine
		limiteSup := limiteInf + intervaloPorGoroutine
		wg.Add(1)
		go worker(limiteInf, limiteSup, h, f, &wg, resultados)
	}

	// Esta goroutine espera a que terminen todas las demás y luego cierra el canal
	go func() {
		wg.Wait()
		close(resultados)
	}()

	areaTotal := 0.0
	// Por ultimo, aquí se ecolecta todos los resultados del canal
	for areaParcial := range resultados {
		areaTotal += areaParcial
	}
	return areaTotal
}
