#include <iostream>
#include <cassert>
#include "OperacionSuma.h"
#include "Calculadora.h"
#include "ProcesadorEntrada.h"

using namespace std;

void run_tests() {
    ProcesadorEntrada p;
    Calculadora c;

    auto nums = p.extraerNumeros("2+3+5");
    assert(c.calcularSuma(nums) == 10);

    auto nums2 = p.extraerNumeros("12+34");
    assert(c.calcularSuma(nums2) == 46);

    auto nums3 = p.extraerNumeros("1+2+3+4+5+6");
    assert(c.calcularSuma(nums3) == 21);

    cout << "[Tests] Todos pasaron correctamente.\n";
}

int main() {
    cout << "=== Calculadora (Lab 1: Suma) ===\n";
    run_tests();

    ProcesadorEntrada p;
    Calculadora c;

    while (true) {
        cout << "\nIngrese operación (ej: 12+34+5) o 'q' para salir:\n> ";
        string linea;
        getline(cin, linea);
        if (linea == "q" || linea == "Q") break;

        try {
            auto nums = p.extraerNumeros(linea);
            long long res = c.calcularSuma(nums);
            cout << "Resultado: " << res << "\n";
        } catch (const exception& e) {
            cerr << "ERROR: " << e.what() << "\n";
        }
    }
    return 0;
}
