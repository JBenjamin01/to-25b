#ifndef OPERACIONMULTIPLICACION_H
#define OPERACIONMULTIPLICACION_H


#include "Operacion.h"


class OperacionMultiplicacion : public Operacion {
public:
    virtual double operar(double a, double b) override;
    virtual char simbolo() const override;
};


#endif // OPERACIONMULTIPLICACION_H