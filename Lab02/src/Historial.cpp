#include "Historial.h"
#include <iostream>
#include <sstream>

Historial::Historial(int initial)
    : capacity(initial), count(0) {
    entries = new std::string*[capacity];
    for (int i = 0; i < capacity; ++i) entries[i] = nullptr;
}

Historial::~Historial() {
    for (int i = 0; i < count; ++i) {
        delete entries[i];
    }
    delete[] entries;
}

void Historial::resize() {
    int newCap = capacity * 2;
    std::string** newArr = new std::string*[newCap];
    for (int i = 0; i < newCap; ++i) newArr[i] = nullptr;
    for (int i = 0; i < count; ++i) newArr[i] = entries[i];
    delete[] entries;
    entries = newArr;
    capacity = newCap;
}

void Historial::anadir(const std::string& expresion, double resultado) {
    std::ostringstream oss;
    oss << expresion << " = " << resultado;
    if (count >= capacity) resize();
    entries[count++] = new std::string(oss.str());
}

void Historial::mostrar() const {
    std::cout << "\n--- Historial de operaciones ---\n";
    for (int i = 0; i < count; ++i) {
        std::cout << (i + 1) << ": " << *entries[i] << "\n";
    }
}
