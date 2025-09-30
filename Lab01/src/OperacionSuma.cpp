#include "OperacionSuma.h"

long long OperacionSuma::sumar(const std::vector<long long>& numeros) const {
    long long res = 0;
    for (auto v : numeros) res += v;
    return res;
}
