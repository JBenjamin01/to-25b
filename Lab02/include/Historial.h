#ifndef HISTORIAL_H
#define HISTORIAL_H

#include <string>

// Historial con arreglo dinamico de punteros a std::string
class Historial {
private:
    std::string** entries; // arreglo dinamico de punteros a string
    int capacity;
    int count;
    void resize();
public:
    Historial(int initial = 10);
    ~Historial();

    void anadir(const std::string& expresion, double resultado);
    void mostrar() const;
};

#endif // HISTORIAL_H
