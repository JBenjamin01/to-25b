#ifndef TAREACALCULO_H
#define TAREACALCULO_H

#include "Funcion.h"

// Con esta clase represento la "hoja de instrucciones" para un solo hilo
class TareaCalculo {
public:
    TareaCalculo(double start_x, double end_x, double h, const Funcion& func);
    void calcular(); // El método que ejecutará el hilo.
    double get_area_parcial() const; // Para obtener el resultado.

private:
    double start_x, end_x, h;
    const Funcion& funcion;
    double area_parcial;
};

#endif