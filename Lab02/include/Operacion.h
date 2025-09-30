#ifndef OPERACION_H
#define OPERACION_H


class Operacion {
public:
    virtual double operar(double a, double b) = 0; // operar la operacion entre a y b
    virtual char simbolo() const = 0; // simbolo del operador
    virtual ~Operacion() {}
};


#endif // OPERACION_H