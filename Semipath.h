#ifndef PROJETO2_SEMIPATH_H
#define PROJETO2_SEMIPATH_H
#include <string>

class Semipath {
public:
    int getStopid() const;
    const std::string &getLine() const;
    const std::string &getName() const;
    Semipath(int stopid, std::string line, std::string name);
private:
    std::string line, name;
    int stopid;
};


#endif //PROJETO2_SEMIPATH_H
