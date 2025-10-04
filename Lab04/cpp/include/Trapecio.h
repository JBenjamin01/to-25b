#ifndef TRAPECIO_H
#define TRAPECIO_H

class Trapecio {
public:
    // Esto le dice al resto del programa: "Existe una función estática
    // llamada calcular_area que toma estos parámetros y devuelve un double".
    static double calcular_area(double y1, double y2, double h);
};

#endif