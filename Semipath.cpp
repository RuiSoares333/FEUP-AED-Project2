#include "Semipath.h"

#include <utility>

/// Getter
/// \return retorna o id da paragem
int Semipath::getStopid() const {
    return stopid;
}

/// Getter
/// \return retorna a linha
const std::string &Semipath::getLine() const {
    return line;
}

/// Getter
/// \return retorna o nome
const std::string &Semipath::getName() const {
    return name;
}

/// Constructor
/// \param stopid inicializa a variável stopid com o valor dado
/// \param line inicializa a variável line com o valor dado
/// \param name inicializa a variável name com o valor dado
Semipath::Semipath(int stopid, std::string line, std::string name){
    this->stopid = stopid;
    this->line = std::move(line);
    this->name = std::move(name);
}

/// Default Constructor
Semipath::Semipath() {}
