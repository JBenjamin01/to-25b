#include <iostream>
using namespace std;

// Clase plantilla para implementar una pila
template<class T>
class Pila {
public:
    Pila(int nelem = 10);
    ~Pila();
    void insertar(T);
    void mostrarPila();
private:
    int nelementos;
    T* cadena;
    int limite;
};

template<class T>
Pila<T>::Pila(int nelem) {
    nelementos = nelem;
    cadena = new T[nelementos]; // usar corchetes, no paréntesis
    limite = 0;
}

template<class T>
Pila<T>::~Pila() {
    delete[] cadena;
}

template<class T>
void Pila<T>::insertar(T elem) {
    if (limite < nelementos)
        cadena[limite++] = elem;
    else
        cout << "La pila está llena.\n";
}

template<class T>
void Pila<T>::mostrarPila() {
    for (int i = 0; i < limite; i++) {
        cout << cadena[i] << ", ";
    }
    cout << endl;
}

int main() {
    Pila<int> pila1(4);
    pila1.insertar(1);
    pila1.insertar(3);
    pila1.mostrarPila();

    Pila<char> pila2(4);
    pila2.insertar('a');
    pila2.insertar('b');
    pila2.insertar('c');
    pila2.mostrarPila();

    return 0;
}
