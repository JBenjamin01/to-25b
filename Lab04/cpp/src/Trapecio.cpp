#include "Trapecio.h"

double Trapecio::calcular_area(double y1, double y2, double h) {
    return ((y1 + y2) * h) / 2.0;
}