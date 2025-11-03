#include <iostream>
#include <string>
using namespace std;

// Nodo genérico (plantilla)
template <typename T>
struct Nodo {
    T dato;
    Nodo* siguiente;
    Nodo(T valor) : dato(valor), siguiente(nullptr) {}
};

// Mi clase plantilla para lista enlazada simple
template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
public:
    ListaEnlazada() : cabeza(nullptr) {}

    void insertar(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (!cabeza) {
            cabeza = nuevo;
        } else {
            Nodo<T>* temp = cabeza;
            while (temp->siguiente)
                temp = temp->siguiente;
            temp->siguiente = nuevo;
        }
    }

    void mostrar() {
        Nodo<T>* temp = cabeza;
        while (temp) {
            cout << temp->dato << " -> ";
            temp = temp->siguiente;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    cout << "Lista de edades (int):" << endl;
    ListaEnlazada<int> listaEdades;
    listaEdades.insertar(18);
    listaEdades.insertar(22);
    listaEdades.insertar(35);
    listaEdades.mostrar();

    cout << "\nLista de palabras (string):" << endl;
    ListaEnlazada<string> listaPalabras;
    listaPalabras.insertar("Hola");
    listaPalabras.insertar("mundo");
    listaPalabras.insertar("C++");
    listaPalabras.mostrar();

    return 0;
}