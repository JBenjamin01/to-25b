#ifndef FUNCION_H
#define FUNCION_H

#include <cmath>

// Un 'struct' en C++ es casi idéntico a una 'class', pero sus miembros son públicos por defecto.
// Lo estamos usando para representar nuestra función matemática f(x).
struct Funcion {
    // Sobrecargamos el operador () para que un objeto de esta clase se pueda "llamar" como una función.
    // Por ejemplo: Funcion f; double y = f(5.0);
    // El 'const' al final indica que este método no modifica el estado del objeto.
    double operator()(double x) const {
        return 2 * std::pow(x, 2) + 3 * x + 0.5;
    }
};

#endif