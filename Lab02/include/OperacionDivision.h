#ifndef OPERACIONDIVISION_H
#define OPERACIONDIVISION_H


#include "Operacion.h"


class OperacionDivision : public Operacion {
public:
    virtual double operar(double a, double b) override;
    virtual char simbolo() const override;
};


#endif // OPERACIONDIVISION_H