#ifndef CALCULADORA_H
#define CALCULADORA_H

#include "Parser.h"
#include "Historial.h"
#include <vector>
#include <string>

class Calculadora {
private:
    Parser* parser;       // puntero al parser
    Historial* historial; // puntero al historial
public:
    Calculadora(Parser* p, Historial* h);
    ~Calculadora();

    // Ejecuta el bucle principal: lee expresiones, las evalua y muestra resultados
    void ejecutar();

    // Evalua el arbol y llena el vector de pasos; devuelve el resultado final
    double evaluar(ExprNode* root, std::vector<std::string>& pasos, int& pasoCount, bool& ok);

    // Recorridos del arbol
    std::string recorridoPreorden(ExprNode* node);
    std::string recorridoInorden(ExprNode* node);
    std::string recorridoPostorden(ExprNode* node);

    // Destruye el arbol liberando memoria
    void destruirArbol(ExprNode*& root);
};

#endif // CALCULADORA_H
