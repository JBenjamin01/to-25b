#include "OperacionDivision.h"
#include <stdexcept>


// Implementacion de la division con validacion de division por cero
double OperacionDivision::operar(double a, double b) {
    if (b == 0.0) {
        throw std::runtime_error("Error: division por cero");
    }
        return a / b;
}


char OperacionDivision::simbolo() const {
    return '/';
}