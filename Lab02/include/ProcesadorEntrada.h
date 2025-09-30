#ifndef PROCESADORENTRADA_H
#define PROCESADORENTRADA_H

#include <string>
#include <vector>
#include <utility>

class ProcesadorEntrada {
public:
    std::pair<std::vector<long long>, char> parsear(const std::string& expresion, size_t maxNums = 6);
};

#endif
