//
// Created by Lucas Gaming on 22/01/2022.
//

#include "Stop.h"

/// Getter
/// \return retorna o código da paragem
const string &Stop::getCode() const {
    return code;
}

/// Setter
/// \param code novo código da paragem
void Stop::setCode(const string &code) {
    Stop::code = code;
}

/// Getter
/// \return retorna o nome da paragem
const string &Stop::getName() const {
    return name;
}

/// Setter
/// \param name novo nome da paragem
void Stop::setName(const string &name) {
    Stop::name = name;
}

/// Getter
/// \return retorna a zona da paragem
const string &Stop::getZone() const {
    return zone;
}

/// Setter
/// \param zone nova zona da paragem
void Stop::setZone(const string &zone) {
    Stop::zone = zone;
}

/// Getter
/// \return retorna a latitude da paragem
double Stop::getLatitude() const {
    return latitude;
}

/// Setter
/// \param latitude nova latitude da paragem
void Stop::setLatitude(double latitude) {
    Stop::latitude = latitude;
}

/// Getter
/// \return retorna a longitude da paragem
double Stop::getLongitude() const {
    return longitude;
}

/// Setter
/// \param longitude nova longitude da paragem
void Stop::setLongitude(double longitude) {
    Stop::longitude = longitude;
}

/// Operador < que recebe uma paragem e compara-a com outra usando o código
/// \param s2 paragem a ser comparada
bool const Stop::operator<(const Stop &s2) const{
    return code < s2.getCode();
}
