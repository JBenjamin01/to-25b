#ifndef OPERACIONRESTA_H
#define OPERACIONRESTA_H


#include "Operacion.h"


class OperacionResta : public Operacion {
public:
    virtual double operar(double a, double b) override;
    virtual char simbolo() const override;
};


#endif // OPERACIONRESTA_H