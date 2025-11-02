#include <iostream>
using namespace std;

// Plantilla de clase para una pareja de valores
template <class T>
class Par {
private:
    T primero, segundo;
public:
    Par(T a, T b) : primero(a), segundo(b) {}

    T getPrimero() const { return primero; }
    T getSegundo() const { return segundo; }

    void mostrar() const {
        cout << "(" << primero << ", " << segundo << ")" << endl;
    }
};

int main() {
    Par<int> p1(10, 20);
    Par<string> p2("Hola", "Mundo");

    p1.mostrar();
    p2.mostrar();

    return 0;
}
