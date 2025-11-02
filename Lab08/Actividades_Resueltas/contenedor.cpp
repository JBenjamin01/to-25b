#include <iostream>
using namespace std;

// Clase plantilla con métodos para insertar y mostrar valores
template<typename T>
class Contenedor {
public:
    T metodo1(int xx) {
        return array[xx];
    }

    void metodo2(T val, int i) {
        if (i >= 0 && i < 4)
            array[i] = val;
    }

    void mostrar() const;
private:
    T array[4];
};

// Definición fuera de la clase
template<typename T>
void Contenedor<T>::mostrar() const {
    for (int i = 0; i < 4; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main() {
    Contenedor<int> z;
    z.metodo2(10, 0);
    z.metodo2(50, 1);
    z.metodo2(60, 2);
    z.metodo2(70, 3);

    cout << "Contenido del contenedor: ";
    z.mostrar();

    return 0;
}
