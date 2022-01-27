#include "Semipath.h"

#include <utility>

int Semipath::getStopid() const {
    return stopid;
}

const std::string &Semipath::getLine() const {
    return line;
}

const std::string &Semipath::getName() const {
    return name;
}

Semipath::Semipath(int stopid, std::string line, std::string name){
    this->stopid = stopid;
    this->line = std::move(line);
    this->name = std::move(name);
}

Semipath::Semipath() {}
