#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "ExprNode.h"

// Parser que convierte una expresion infija a un arbol de expresion
class Parser {
public:
    Parser();
    ~Parser();

    // Devuelve puntero al nodo raiz (el llamador debe destruir el arbol o usar destruirArbol)
    ExprNode* parse(const std::string& expr);

private:
    int precedence(char op);
    bool esOperador(const std::string& token);
    Operacion* crearOperacion(char op);
    std::vector<std::string> tokenize(const std::string& expr);
    std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens);
};

#endif // PARSER_H
