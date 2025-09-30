#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <vector>
#include "OperacionSuma.h"

class Calculadora {
private:
    OperacionSuma suma;
public:
    long long calcularSuma(const std::vector<long long>& numeros);
};

#endif
