#include "TareaCalculo.h"
#include "Trapecio.h"

// El constructor simplemente inicializa los datos de la tarea.
TareaCalculo::TareaCalculo(double start_x, double end_x, double h, const Funcion& func)
    : start_x(start_x), end_x(end_x), h(h), funcion(func), area_parcial(0.0) {}

double TareaCalculo::get_area_parcial() const {
    return area_parcial;
}

// Esta seria basicamente la lógica que cada hilo ejecuta para su parte
void TareaCalculo::calcular() {
    double x_actual = start_x;
    while (x_actual < end_x) {
        double y1 = funcion(x_actual);
        double y2 = funcion(x_actual + h);
        area_parcial += Trapecio::calcular_area(y1, y2, h);
        x_actual += h;
    }
}