#include <iostream>
using namespace std;

// Función plantilla genérica para devolver el mayor de dos valores
template <typename Tipo>
Tipo mayorDe(Tipo a, Tipo b) {
    return (a > b ? a : b);
}

int main() {
    char x = mayorDe<char>('e', 'z');
    int y = mayorDe<int>(9, 4);
    double z = mayorDe<double>(5.8, 2.3);

    cout << "Caracter mayor: " << x << endl;
    cout << "Numero mayor: " << y << endl;
    cout << "Numero mayor (double): " << z << endl;

    return 0;
}