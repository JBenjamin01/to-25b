#include <QCoreApplication>
#include <QDebug>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Función lambda que suma 3
    auto sumar = [](int valor) { return valor + 3; };

    int u = 7;
    qDebug() << "Resultado de la suma:" << sumar(u);

    // Vector de enteros
    vector<int> v {5, 2, 3, 7, 1, 0, 14, 20};

    qDebug() << "Elementos del vector:";
    for_each(v.begin(), v.end(), [](int valor) {
        qDebug() << valor;
    });

    return 0;
}
