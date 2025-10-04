#ifndef CALCULADORINTEGRAL_H
#define CALCULADORINTEGRAL_H

#include "Funcion.h"
#include <thread>

// Aquí coloco la lógica principal del cálculo.
class CalculadorIntegral {
public:
    CalculadorIntegral(const Funcion& func, double a, double b);

    double calcular(int n_trapecios);

private:
    const Funcion& funcion;
    double a;
    double b;
    int num_hilos;
};

#endif