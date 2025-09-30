#ifndef OPERACIONSUMA_H
#define OPERACIONSUMA_H


#include "Operacion.h"


class OperacionSuma : public Operacion {
public:
    virtual double operar(double a, double b) override;
    virtual char simbolo() const override;
};


#endif // OPERACIONSUMA_H