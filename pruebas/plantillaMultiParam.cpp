#include <iostream>
using namespace std;

// Plantilla con dos tipos genéricos y un valor entero
template <typename T, typename U, int N>
class Arreglo {
private:
    T datos[N];
public:
    void llenar(U valor) {
        for (int i = 0; i < N; i++)
            datos[i] = static_cast<T>(valor);
    }

    void mostrar() const {
        for (int i = 0; i < N; i++)
            cout << datos[i] << " ";
        cout << endl;
    }
};

int main() {
    Arreglo<int, double, 5> arr;
    arr.llenar(3.14);
    arr.mostrar(); // Imprime: 3 3 3 3 3
    return 0;
}
