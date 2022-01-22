#ifndef PROJETO2_BASEDADOS_H
#define PROJETO2_BASEDADOS_H

#include "graph.h"
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "Stop.h"

using namespace std;

class BaseDados {
private:
    map<int, Stop> stopMap;
    Graph dGraph, mGraph;

public:
    BaseDados(Graph dGraph, Graph mGraph, map<int, Stop> stopMap);
    void loadAllLines();
    void loadLine(string code, string name);
    static double haversine(double lat1, double lon1, double lat2, double lon2);
    Graph getDGraph() const;
    Graph getMGraph() const;
};
#endif //PROJETO2_BASEDADOS_H
