#ifndef EXPRNODE_H
#define EXPRNODE_H


#include <string>
#include "Operacion.h"


// Nodo del arbol de expresion
class ExprNode {
public:
    bool isOperator; // true si es operador
    Operacion* oper; // puntero a la operacion (si es nodo operador)
    double value; // valor si es hoja
    ExprNode* left; // hijo izquierdo
    ExprNode* right; // hijo derecho


    // constructor para hoja (numero)
    ExprNode(double val);
    // constructor para nodo operador
    ExprNode(Operacion* operacion, ExprNode* left, ExprNode* right);
    // destructor libera operacion y subarboles
    ~ExprNode();


    // obtener cadena infija con parentesis que representa el subarbol
    std::string toInfix() const;
};


#endif // EXPRNODE_H