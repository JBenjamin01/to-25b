#include <iostream>
#include "Parser.h"
#include "Calculadora.h"
#include "Historial.h"

int main() {
    // Crear objetos como punteros (actividad 02)
    Parser* parser = new Parser();
    Historial* historial = new Historial(10);
    Calculadora* calc = new Calculadora(parser, historial);

    // Ejecutar la calculadora (loop de entrada)
    calc->ejecutar();

    // Liberar memoria de los objetos creados con new
    delete calc;
    delete parser;
    delete historial;

    return 0;
}
