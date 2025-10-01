#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void tareaPesada(string nombre) {
    cout << nombre << " empieza\n";
    // Simular trabajo que dura 2 segundos
    this_thread::sleep_for(chrono::seconds(2));
    cout << nombre << " termina\n";
}

int main() {
    auto inicio = chrono::high_resolution_clock::now();

    thread t1(tareaPesada, "Hilo 1");
    thread t2(tareaPesada, "Hilo 2");

    t1.join();
    t2.join();

    auto fin = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::seconds>(fin - inicio).count();

    cout << "Tiempo total: " << duracion << " segundos\n";
    return 0;
}
