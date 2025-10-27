#include <QCoreApplication>
#include <QDebug>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    srand(time(nullptr));

    vector<int> numeros;
    for (int i = 0; i < 20; ++i)
        numeros.push_back(rand() % 50); // genera números entre 0 y 49

    // contar los impares menores de 20
    int cantidad = count_if(numeros.begin(), numeros.end(), [](int n) {
        return (n % 2 != 0 && n < 20);
    });

    qDebug() << "Vector generado:";
    for (int n : numeros)
        qDebug() << n;

    qDebug() << "Cantidad de impares menores de 20:" << cantidad;

    return 0;
}
