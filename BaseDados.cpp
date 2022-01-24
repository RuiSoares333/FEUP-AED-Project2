#include <cmath>
#include "BaseDados.h"

map<Stop, double> BaseDados::nearStops(double lat, double lon, double radius) {

    map<Stop, double> nearStopsMap;
    map<int, Stop>::iterator iter;
    double distance;

    for (iter = stopMap.begin(); iter != stopMap.end(); iter++) {
        distance = haversine(lat, lon, iter->second.getLatitude(), iter->second.getLongitude());
        if (distance <= radius)
            nearStopsMap[iter->second] = distance;
    }

    return nearStopsMap;
}

map<Stop, double> BaseDados::nearestStop(double lat, double lon) {
    map<Stop, double> nearestStopMap;
    map<int, Stop>::iterator iter = stopMap.begin();
    double distance = haversine(lat, lon, iter->second.getLatitude(), iter->second.getLongitude()), newDistance;
    Stop nearestStop;

    for (iter = stopMap.begin(); iter != stopMap.end(); iter++) {
        newDistance = haversine(lat, lon, iter->second.getLatitude(), iter->second.getLongitude());
        if (newDistance < distance) {
            nearestStop = iter->second;
            distance = newDistance;
        }
    }

    nearestStopMap[nearestStop] = distance;
    return nearestStopMap;
}

void BaseDados::loadAllLines() {
    ifstream lines;
    lines.open("../dataset/lines.csv");
    if(lines.is_open()){
        string throwaway, code, name, line;
        getline(lines, throwaway);

        while(getline(lines, line)){
            stringstream sep(line);
            getline(sep, code, ',');
            getline(sep, name, '\n');

            loadLine(code, name);
        }
    }
    else throw ("Lines.csv file not found in dataset folder!");
}

void BaseDados::loadLine(string code, string name) {
    ifstream line;
    int n, stopid, nextid;
    string stop, next;
    double weight;

    for (int i = 0; i < 2; i++){
        string rev = "";
        if(i == 1) rev = "_rev";
        if((code == "300" or code == "301" or code == "302" or code == "303") && i == 1) continue;
        line.open("../dataset/line_" + code + "_" + to_string(i) + ".csv");

        if(line.is_open()){
            line >> n;
            line >> stop;
            for (int j = 2; j <= n; j++){
                line >> next;

                stopid = reverseStopMap[stop];
                nextid = reverseStopMap[next];

                weight = haversine(stopMap[stopid].getLatitude(), stopMap[stopid].getLongitude(), stopMap[nextid].getLatitude(), stopMap[nextid].getLongitude());
                mGraph.addEdge(stopid, nextid, weight, code, name);
                if(code[code.length() - 1] != 'M') dGraph.addEdge(stopid, nextid, weight, code+rev, name);
                stop = next;
            }
        }
        else throw ("line_" + code + "_" + to_string(i) + ".csv not found in dataset folder!");
    }
}

/*
void BaseDados::loadLine(string code, string name) {
    ifstream line;
    int n;
    string stop, next;
    int stopid, nextid;
    double weight;
    bool foundid1, foundid2;
    if(code == "300" or code == "301" or code == "302" or code == "303"){
        //circulares - apenas tem dir = 0
        line.open("../dataset/line_" + code + "_0.csv");
        if(line.is_open()){
            line >> n;
            line >> stop;
            for (int j = 0; j < n -1; j++){
                foundid1 = false, foundid2 = false;
                line >> next;
                for (int k = 1; k <= stopMap.size(); k++){
                    if(stopMap[k].getCode() == stop){
                        stopid = k;
                        foundid1 = true;
                    }
                    else if(stopMap[k].getCode() == next){
                        nextid = k;
                        foundid2 = true;
                    }
                    if(foundid1 && foundid2) break;
                }
                weight = haversine(stopMap[stopid].getLatitude(), stopMap[stopid].getLongitude(), stopMap[nextid].getLatitude(), stopMap[nextid].getLongitude());
                mGraph.addEdge(stopid, nextid, weight, code);
                dGraph.addEdge(stopid, nextid, weight, code);
                stop = next;
            }
        } else throw ("line_" + code + "_0.csv not found in dataset folder!");
    }
    else if(code[code.length()-1] == 'M'){
        //linhas madrugada - apenas adicionar ao grafo madrugada
        for (int i = 0; i < 2; i++){
            line.open("../dataset/line_" + code + "_" + to_string(i) + ".csv");
            if(line.is_open()){
                line >> n;
                line >> stop;
                for (int j = 0; j < n -1; j++){
                    foundid1 = false, foundid2 = false;
                    line >> next;
                    for (int k = 1; k <= stopMap.size(); k++){
                        if(stopMap[k].getCode() == stop){
                            stopid = k;
                            foundid1 = true;
                        }
                        else if(stopMap[k].getCode() == next){
                            nextid = k;
                            foundid2 = true;
                        }
                        if(foundid1 && foundid2) break;
                    }
                    weight = haversine(stopMap[stopid].getLatitude(), stopMap[stopid].getLongitude(), stopMap[nextid].getLatitude(), stopMap[nextid].getLongitude());
                    mGraph.addEdge(stopid, nextid, weight, code);
                    stop = next;
                }
            } else throw ("line_" + code + "_" + to_string(i) + ".csv not found in dataset folder!");
        }
    }
    else{
        for (int i = 0; i < 2; i++){
            line.open("../dataset/line_" + code + "_" + to_string(i) + ".csv");
            if(line.is_open()){
                line >> n;
                line >> stop;
                for (int j = 0; j < n -1; j++){
                    foundid1 = false, foundid2 = false;
                    line >> next;
                    for (int k = 1; k <= stopMap.size(); k++){
                        if(stopMap[k].getCode() == stop){
                            stopid = k;
                            foundid1 = true;
                        }
                        else if(stopMap[k].getCode() == next){
                            nextid = k;
                            foundid2 = true;
                        }
                        if(foundid1 && foundid2) break;
                    }
                    weight = haversine(stopMap[stopid].getLatitude(), stopMap[stopid].getLongitude(), stopMap[nextid].getLatitude(), stopMap[nextid].getLongitude());
                    dGraph.addEdge(stopid, nextid, weight, code);
                    mGraph.addEdge(stopid, nextid, weight, code);
                    stop = next;
                }
            } else throw ("line_" + code + "_" + to_string(i) + ".csv not found in dataset folder!");
        }
    }
}
 */

double BaseDados::haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

BaseDados::BaseDados(Graph dGraph, Graph mGraph, map<int, Stop> stopMap, map<string, int> reverseStopMap) : dGraph(dGraph), mGraph(mGraph) {
    this->stopMap = stopMap;
    this->reverseStopMap = reverseStopMap;
}

Graph BaseDados::getDGraph() const {
    return dGraph;
}

Graph BaseDados::getMGraph() const {
    return mGraph;
}
