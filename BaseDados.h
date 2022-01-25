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
    map<string, int> reverseStopMap;
    Graph dGraph, mGraph, pdGraph, pmGraph;
public:
    const Graph &getPdGraph() const;

    const Graph &getPmGraph() const;

public:
    BaseDados(Graph dGraph, Graph mGraph, Graph pdGraph, Graph pmGraph, map<int, Stop> stopMap, map<string, int> reverseStopMap);
    void loadAllLines();
    void loadLine(string code, string name);
    static double haversine(double lat1, double lon1, double lat2, double lon2);
    Graph getDGraph() const;
    Graph getMGraph() const;
    map<int, Stop> getStopMap() const;
    map<string, int> getReverseStopMap() const;
    map<Stop, double> nearStops(double lat, double lon, double radius);
    map<Stop, double> nearestStop(double lat, double lon);
    void onFootStops();
};
#endif //PROJETO2_BASEDADOS_H
