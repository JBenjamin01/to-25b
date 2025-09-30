#include "ProcesadorEntrada.h"
#include <cctype>
#include <stdexcept>

std::pair<std::vector<long long>, char> ProcesadorEntrada::parsear(const std::string& expresion, size_t maxNums) {
    std::vector<long long> numeros;
    char oper = 0;
    long long num = 0;
    bool leyendoNumero = false;
    bool negativo = false;

    for (size_t i = 0; i < expresion.size(); ++i) {
        char c = expresion[i];

        if (isspace((unsigned char)c)) continue;

        if (c == '-' && (i == 0 || !isdigit(expresion[i-1]))) {
            negativo = true;
            continue;
        }

        if (isdigit((unsigned char)c)) {
            leyendoNumero = true;
            num = num * 10 + (c - '0');
        } else {
            if (leyendoNumero) {
                if (negativo) { num = -num; negativo = false; }
                numeros.push_back(num);
                if (numeros.size() > maxNums) throw std::runtime_error("Maximo de numeros excedido.");
                num = 0; leyendoNumero = false;
            }

            if (c=='+'||c=='-'||c=='*'||c=='/') {
                if (oper == 0) oper = c;
                else if (oper != c) throw std::runtime_error("Solo se admite un operador por expresion en esta version.");
            } else {
                throw std::runtime_error("Carácter invalido en expresion.");
            }
        }
    }

    if (leyendoNumero) {
        if (negativo) num = -num;
        numeros.push_back(num);
    }

    if (numeros.empty()) throw std::runtime_error("Expresion vacia.");
    return {numeros, oper};
}
