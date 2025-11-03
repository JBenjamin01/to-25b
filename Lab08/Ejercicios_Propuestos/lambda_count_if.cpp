#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> numeros = {3, 7, 10, 4, 8, 15, 2};

    // Contar cuántos números son mayores que 5 usando una lambda
    int mayores5 = count_if(numeros.begin(), numeros.end(), [](int n) {
        return n > 5;
    });

    // Contar cuántos son pares
    int pares = count_if(numeros.begin(), numeros.end(), [](int n) {
        return n % 2 == 0;
    });

    cout << "Cantidad de numeros mayores que 5: " << mayores5 << endl;
    cout << "Cantidad de numeros pares: " << pares << endl;

    return 0;
}
