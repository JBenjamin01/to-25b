#include <iostream>
using namespace std;

// Plantilla de función para devolver el máximo de dos valores
template <typename T>
T maximo(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    cout << "Máximo entre 5 y 10: " << maximo(5, 10) << endl;           // int
    cout << "Máximo entre 3.14 y 2.71: " << maximo(3.14, 2.71) << endl; // double
    cout << "Máximo entre 'a' y 'z': " << maximo('a', 'z') << endl;     // char
    return 0;
}
