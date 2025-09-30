#include "OperacionResta.h"


// Implementacion de la resta
double OperacionResta::operar(double a, double b) {
    return a - b;
}


char OperacionResta::simbolo() const {
    return '-';
}