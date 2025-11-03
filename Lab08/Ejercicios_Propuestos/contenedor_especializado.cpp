#include <iostream>
using namespace std;

// Plantilla general
template<class T>
class Contenedor {
    T elemento;
public:
    Contenedor(T arg) { elemento = arg; }
    T add() { return ++elemento; }
};

// Especialización para tipo char
template<>
class Contenedor<char> {
    char elemento;
public:
    Contenedor(char arg) { elemento = arg; }
    char uppercase() {
        if ((elemento >= 'a') && (elemento <= 'z')) {
            elemento += 'A' - 'a';
        }
        return elemento;
    }
};

int main() {
    Contenedor<int> cint(5);
    Contenedor<char> cchar('t');
    cout << cint.add() << endl;
    cout << cchar.uppercase() << endl;
    return 0;
}