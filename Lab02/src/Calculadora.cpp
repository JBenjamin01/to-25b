#include "Calculadora.h"
#include <iostream>
#include <sstream>
#include <cmath>

// Funcion recursiva auxiliar para evaluar y registrar pasos
static double evalRec(ExprNode* node, std::vector<std::string>& pasos, int& pasoCount, bool& ok) {
    if (!node) { ok = false; return 0.0; }
    if (!node->isOperator) {
        return node->value;
    }
    double left = evalRec(node->left, pasos, pasoCount, ok);
    double right = evalRec(node->right, pasos, pasoCount, ok);
    if (!ok) return 0.0;
    double res = 0.0;
    try {
        res = node->oper->operar(left, right);
    } catch (const std::exception& e) {
        // error (por ejemplo division por cero)
        pasos.push_back(std::string("Error: ") + e.what());
        ok = false;
        return 0.0;
    }
    // Registrar paso
    std::ostringstream oss;
    oss << "Paso " << pasoCount << ": " << left << node->oper->simbolo() << right << " = " << res;
    pasos.push_back(oss.str());
    pasoCount++;
    return res;
}

Calculadora::Calculadora(Parser* p, Historial* h)
    : parser(p), historial(h) {}

Calculadora::~Calculadora() {
    // no borramos parser ni historial aqui; el main controla la vida de esos objetos
}

double Calculadora::evaluar(ExprNode* root, std::vector<std::string>& pasos, int& pasoCount, bool& ok) {
    ok = true;
    pasoCount = 1;
    pasos.clear();
    double res = evalRec(root, pasos, pasoCount, ok);
    return res;
}

// Recorridos que devuelven una cadena
std::string Calculadora::recorridoPreorden(ExprNode* node) {
    if (!node) return "";
    std::ostringstream oss;
    if (node->isOperator) oss << node->oper->simbolo() << " ";
    else oss << node->value << " ";
    oss << recorridoPreorden(node->left);
    oss << recorridoPreorden(node->right);
    return oss.str();
}

std::string Calculadora::recorridoInorden(ExprNode* node) {
    if (!node) return "";
    if (!node->isOperator) {
        std::ostringstream oss; oss << node->value << " "; return oss.str();
    }
    std::ostringstream oss;
    oss << "( ";
    oss << recorridoInorden(node->left);
    oss << node->oper->simbolo() << " ";
    oss << recorridoInorden(node->right);
    oss << ") ";
    return oss.str();
}

std::string Calculadora::recorridoPostorden(ExprNode* node) {
    if (!node) return "";
    std::ostringstream oss;
    oss << recorridoPostorden(node->left);
    oss << recorridoPostorden(node->right);
    if (node->isOperator) oss << node->oper->simbolo() << " "; else oss << node->value << " ";
    return oss.str();
}

void Calculadora::destruirArbol(ExprNode*& root) {
    // borrar la raiz libera recursivamente todos los nodos en ExprNode destructor
    delete root;
    root = nullptr;
}

void Calculadora::ejecutar() {
    std::cout << "Calculadora con arbol de expresion\n";
    std::cout << "Escriba una expresion, 'h' para ver historial o 'exit' para salir. Soportado: + - * / y parentesis. Ej: 12+4*3\n";
    std::string linea;
    while (true) {
        std::cout << "\n> ";
        if (!std::getline(std::cin, linea)) break;
        if (linea.empty()) continue;
        if (linea == "exit" || linea == "quit") break;

        if (linea == "h" || linea == "historial") {
            if (historial) historial->mostrar();
                continue;
        }

        ExprNode* root = nullptr;
        try {
            root = parser->parse(linea);
        } catch (const std::exception& e) {
            std::cout << "Error al parsear: " << e.what() << "\n";
            continue;
        }

        std::vector<std::string> pasos;
        int pasoCount = 1;
        bool ok = true;
        double resultado = evaluar(root, pasos, pasoCount, ok);

        if (ok) {
            // mostrar pasos
            std::cout << "\n--- Evaluacion paso a paso ---\n";
            for (size_t i = 0; i < pasos.size(); ++i) std::cout << pasos[i] << "\n";
            std::cout << "\nResultado final: " << resultado << "\n";

            // agregar al historial
            if (historial) historial->anadir(linea, resultado);

            // mostrar recorridos
            std::cout << "\nRecorridos:\n";
            std::cout << "Preorden: " << recorridoPreorden(root) << "\n";
            std::cout << "Inorden : " << recorridoInorden(root) << "\n";
            std::cout << "Postorden: " << recorridoPostorden(root) << "\n";
        } else {
            std::cout << "No se pudo evaluar la expresion por error\n";
        }

        // destruir arbol
        destruirArbol(root);
    }

    // al salir, mostrar historial
    if (historial) historial->mostrar();
}
