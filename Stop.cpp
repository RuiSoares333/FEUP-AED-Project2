//
// Created by Lucas Gaming on 22/01/2022.
//

#include "Stop.h"

const string &Stop::getCode() const {
    return code;
}

void Stop::setCode(const string &code) {
    Stop::code = code;
}

const string &Stop::getName() const {
    return name;
}

void Stop::setName(const string &name) {
    Stop::name = name;
}

const string &Stop::getZone() const {
    return zone;
}

void Stop::setZone(const string &zone) {
    Stop::zone = zone;
}

double Stop::getLatitude() const {
    return latitude;
}

void Stop::setLatitude(double latitude) {
    Stop::latitude = latitude;
}

double Stop::getLongitude() const {
    return longitude;
}

void Stop::setLongitude(double longitude) {
    Stop::longitude = longitude;
}

bool const Stop::operator<(const Stop &s2) const{
    return code < s2.getCode();
}
