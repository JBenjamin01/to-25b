#include "ProcesadorEntrada.h"
#include <cctype>

std::vector<long long> ProcesadorEntrada::extraerNumeros(const std::string& expresion, size_t maxNums) {
    std::vector<long long> numeros;
    size_t n = expresion.size();
    size_t i = 0;

    while (i < n) {
        while (i < n && isspace((unsigned char)expresion[i])) ++i;
        if (i >= n) break;

        if (expresion[i] == '-') {
            throw InputError("Números negativos no soportados en la versión básica (Lab 1).");
        }

        if (!isdigit((unsigned char)expresion[i])) {
            throw InputError("Entrada inválida: se esperaba un número.");
        }

        long long val = 0;
        while (i < n && isdigit((unsigned char)expresion[i])) {
            val = val * 10 + (expresion[i] - '0');
            ++i;
        }
        numeros.push_back(val);
        if (numeros.size() > maxNums) {
            throw LimitExceeded("Máximo permitido de " + std::to_string(maxNums) + " números.");
        }

        while (i < n && isspace((unsigned char)expresion[i])) ++i;
        if (i >= n) break;

        if (expresion[i] != '+') {
            throw InputError("Operador inválido: solo '+' permitido en Lab 1.");
        }
        ++i; // consumir '+'
    }

    if (numeros.empty()) {
        throw InputError("Expresión vacía o sin números.");
    }
    return numeros;
}
