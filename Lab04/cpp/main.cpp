#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <chrono>

#include "CalculadorIntegral.h"
#include "Funcion.h"

int main() {
    const double A = 2.0;
    const double B = 20.0;
    const int NUM_HILOS = std::thread::hardware_concurrency();

    Funcion f;
    CalculadorIntegral calculador(f, A, B);

    // --- Mensajito inicial mejorado ---
    std::cout << "+ Iniciando calculo con la siguiente configuracion:" << std::endl;
    std::cout << "- Funcion: f(x) = 2x^2 + 3x + 0.5" << std::endl;
    std::cout << "- Limites: [" << A << ", " << B << "]" << std::endl;
    std::cout << "- Hilos detectados: " << NUM_HILOS << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    // --- INICIO DE LA MEDICIÓN DE TIEMPO ---
    auto start = std::chrono::high_resolution_clock::now();

    double area_anterior = 0.0;
    double area_actual = -1.0;
    int n_trapecios = 1;
    const double TOLERANCIA = 1e-7; // Criterio de parada

    std::cout << "Calculando..." << std::endl;
    std::cout << std::fixed << std::setprecision(8);

    // En esta parte hago que el bucle se detenga cuando el resultado ya no cambia significativamente
    while (std::abs(area_actual - area_anterior) > TOLERANCIA) {
        area_anterior = area_actual;
        // Cada llamada a 'calcular' ahora ejecutará el trabajo en paralelo.
        area_actual = calculador.calcular(n_trapecios);
        std::cout << "Trapecios: " << n_trapecios << ", Area: " << area_actual << std::endl;

        // Para mejorar la convergencia se duplica
        n_trapecios *= 2;
    }

    // --- FIN PARA LA MEDICIÓN DE TIEMPO ---
    auto end = std::chrono::high_resolution_clock::now();

    // Duración total en milisegundos.
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();


    // --- RESUMEN FINAL ---
    std::cout << "\n--- RESUMEN DE EJECUCION ---" << std::endl;
    std::cout << "Resultado final estable." << std::endl;
    std::cout << "- Area calculada:      " << area_actual << std::endl;
    std::cout << "- Trapecios usados:     " << n_trapecios / 2 << std::endl; // El último valor se duplicó, así que lo dividimos.
    std::cout << "- Hilos de ejecucion:   " << NUM_HILOS << std::endl;
    std::cout << "- Tiempo total:         " << duration_ms << " ms" << std::endl;
    std::cout << "--------------------------" << std::endl;

    return 0;
}