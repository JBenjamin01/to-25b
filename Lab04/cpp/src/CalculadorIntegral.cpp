#include "CalculadorIntegral.h"
#include "TareaCalculo.h"
#include <vector>
#include <thread>

// El constructor ahora determina cuántos hilos usar.
CalculadorIntegral::CalculadorIntegral(const Funcion& func, double a, double b)
    : funcion(func), a(a), b(b) {
    // std::thread::hardware_concurrency() detecta los núcleos lógicos de mi CPU.
    num_hilos = std::thread::hardware_concurrency();
}

double CalculadorIntegral::calcular(int n_trapecios) {
    double h = (b - a) / n_trapecios;
    double intervalo_por_hilo = (b - a) / num_hilos;
    
    std::vector<std::thread> hilos;
    std::vector<TareaCalculo*> tareas; // Aqui uso punteros para la gestión dinámica.

    // DIVIDIR Y ASIGNAR TRABAJO
    for (int i = 0; i < num_hilos; ++i) {
        double limite_inf = a + i * intervalo_por_hilo;
        double limite_sup = limite_inf + intervalo_por_hilo;

        // Creamos la tarea en el heap.
        TareaCalculo* tarea = new TareaCalculo(limite_inf, limite_sup, h, funcion);
        tareas.push_back(tarea);
        
        // Creamos y lanzamos el hilo, dándole su tarea.
        hilos.emplace_back(&TareaCalculo::calcular, tarea);
    }

    double area_total = 0.0;

    // ESPERAR Y RECOLECTAR RESULTADOS
    for (int i = 0; i < num_hilos; ++i) {
        hilos[i].join(); // El hilo principal espera a que el hilo trabajador termine.
        area_total += tareas[i]->get_area_parcial();
    }

    // Aqui solo limpio la memoria
    for (TareaCalculo* tarea : tareas) {
        delete tarea;
    }

    return area_total;
}