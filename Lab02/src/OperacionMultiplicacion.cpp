#include "OperacionMultiplicacion.h"


// Implementacion de la multiplicacion
double OperacionMultiplicacion::operar(double a, double b) {
    return a * b;
}


char OperacionMultiplicacion::simbolo() const {
    return '*';
}