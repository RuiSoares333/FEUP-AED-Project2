#ifndef PROJETO2_STOP_H
#define PROJETO2_STOP_H

#include <iostream>

using namespace std;

class Stop {

public:
    const string &getCode() const;

    void setCode(const string &code);

    const string &getName() const;

    void setName(const string &name);

    const string &getZone() const;

    void setZone(const string &zone);

    double getLatitude() const;

    void setLatitude(double latitude);

    double getLongitude() const;

    void setLongitude(double longitude);

private:
    string code, name, zone;
    double latitude, longitude;
};


#endif //PROJETO2_STOP_H
