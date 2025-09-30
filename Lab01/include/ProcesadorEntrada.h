#ifndef PROCESADORENTRADA_H
#define PROCESADORENTRADA_H

#include <string>
#include <vector>
#include <stdexcept>

// Excepciones personalizadas
struct InputError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct LimitExceeded : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class ProcesadorEntrada {
public:
    std::vector<long long> extraerNumeros(const std::string& expresion, size_t maxNums = 6);
};

#endif
