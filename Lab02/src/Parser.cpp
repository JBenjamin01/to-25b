#include "Parser.h"
#include "OperacionSuma.h"
#include "OperacionResta.h"
#include "OperacionMultiplicacion.h"
#include "OperacionDivision.h"

#include <stack>
#include <cctype>
#include <sstream>
#include <stdexcept>

Parser::Parser() {}
Parser::~Parser() {}

int Parser::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool Parser::esOperador(const std::string& token) {
    return token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/');
}

Operacion* Parser::crearOperacion(char op) {
    switch (op) {
        case '+': return new OperacionSuma();
        case '-': return new OperacionResta();
        case '*': return new OperacionMultiplicacion();
        case '/': return new OperacionDivision();
        default: return nullptr;
    }
}

// Tokeniza la expresion: numeros (enteros o decimales), operadores y parentesis
std::vector<std::string> Parser::tokenize(const std::string& expr) {
    std::vector<std::string> tokens;
    size_t i = 0;
    while (i < expr.size()) {
        char c = expr[i];
        if (isspace((unsigned char)c)) { i++; continue; }
        if (isdigit((unsigned char)c) || c == '.') {
            // numero
            size_t j = i;
            while (j < expr.size() && (isdigit((unsigned char)expr[j]) || expr[j] == '.')) j++;
            tokens.push_back(expr.substr(i, j - i));
            i = j;
            continue;
        }
        if (c == '+' || c == '*' || c == '/' ) {
            std::string s(1, c);
            tokens.push_back(s);
            i++;
            continue;
        }
        if (c == '-') {
            // determinar si es menos unario (negativo) o operador binario
            // si es al inicio o despues de '(' o de otro operador, se considera unario
            bool unario = false;
            if (tokens.empty()) unario = true;
            else {
                std::string last = tokens.back();
                if (last == "(" || esOperador(last)) unario = true;
            }
            if (unario) {
                // convertir '-X' en '0 - X' para facilitar el parser
                tokens.push_back("0");
                tokens.push_back("-");
            } else {
                tokens.push_back(std::string(1, '-'));
            }
            i++;
            continue;
        }
        if (c == '(' || c == ')') {
            tokens.push_back(std::string(1, c));
            i++;
            continue;
        }
        // caracter invalido
        throw std::runtime_error(std::string("Token invalido: ") + c);
    }
    return tokens;
}

// Algoritmo shunting-yard para obtener postfix
std::vector<std::string> Parser::infixToPostfix(const std::vector<std::string>& tokens) {
    std::vector<std::string> output;
    std::stack<std::string> ops;

    for (const std::string& tok : tokens) {
        if (tok.empty()) continue;
        if (esOperador(tok)) {
            char op = tok[0];
            while (!ops.empty() && esOperador(ops.top())) {
                char topOp = ops.top()[0];
                if ( (precedence(topOp) > precedence(op)) || (precedence(topOp) == precedence(op)) ) {
                    output.push_back(ops.top());
                    ops.pop();
                } else break;
            }
            ops.push(tok);
        } else if (tok == "(") {
            ops.push(tok);
        } else if (tok == ")") {
            while (!ops.empty() && ops.top() != "(") {
                output.push_back(ops.top());
                ops.pop();
            }
            if (ops.empty()) throw std::runtime_error("Parentesis no balanceados");
            ops.pop(); // quitar '('
        } else {
            // numero
            output.push_back(tok);
        }
    }
    while (!ops.empty()) {
        if (ops.top() == "(" || ops.top() == ")") throw std::runtime_error("Parentesis no balanceados");
        output.push_back(ops.top());
        ops.pop();
    }
    return output;
}

// Construye el arbol de expresion a partir de la expresion infija
ExprNode* Parser::parse(const std::string& expr) {
    std::vector<std::string> tokens = tokenize(expr);
    std::vector<std::string> postfix = infixToPostfix(tokens);

    std::stack<ExprNode*> stack;
    for (const std::string& tok : postfix) {
        if (esOperador(tok)) {
            // operador binario: sacar dos operandos
            if (stack.size() < 2) throw std::runtime_error("Expresion invalida: faltan operandos");
            ExprNode* right = stack.top(); stack.pop();
            ExprNode* left = stack.top(); stack.pop();
            Operacion* oper = crearOperacion(tok[0]);
            ExprNode* node = new ExprNode(oper, left, right);
            stack.push(node);
        } else {
            // numero
            double val = 0.0;
            try {
                val = std::stod(tok);
            } catch (...) {
                throw std::runtime_error(std::string("Numero invalido: ") + tok);
            }
            ExprNode* node = new ExprNode(val);
            stack.push(node);
        }
    }
    if (stack.size() != 1) throw std::runtime_error("Expresion invalida: error en parseo");
    return stack.top();
}
