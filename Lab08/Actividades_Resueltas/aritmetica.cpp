#include <iostream>
using namespace std;

// Función plantilla para realizar operaciones aritméticas
template<typename mitipo>
mitipo aritmetica(mitipo x, mitipo y) {
    return x + y;
}

int main() {
    cout << "Resultado (int): " << aritmetica<int>(10, 45) << endl;
    cout << "Resultado (double): " << aritmetica<double>(3.45, 8.10) << endl;
    cout << "Resultado (float): " << aritmetica<float>(0.14f, 0.147f) << endl;

    return 0;
}