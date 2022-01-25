#include <algorithm>
#include <iostream>
#include "Menu.h"
#include <map>
#include "BaseDados.h"

using namespace std;

void diaNoiteMenu(const BaseDados& bd);
void parCorMenu(bool dia, const BaseDados& bd);
void getTravel(bool dia, int paragem1, int paragem2);
int getParagem(bool paragens, bool origem, const BaseDados& bd);
map<int, Stop> loadStops();
map<string, int> reverseStops(map<int, Stop> map1);

int main() {
    map<int, Stop> stopMap = loadStops();
    map<string, int> reverseStopMap = reverseStops(stopMap);
    Graph dGraph(stopMap.size());
    Graph mGraph(stopMap.size());
    Graph pdGraph = dGraph;
    Graph pmGraph = mGraph;
    BaseDados bd = BaseDados(dGraph, mGraph, pdGraph, pmGraph, stopMap, reverseStopMap); //stopmap<id, stop>  reversestopmap<code, id>
    bd.loadAllLines();

    bd.onFootStops();

//    cout << d.bfs_distance(235, 2119) << endl;
//
//    list<Semipath> bfs_path = d.bfs_path(235, 2119);
//    if(bfs_path.size() == 0){
//        cout << -1 << endl;
//    }
//    else{
//        list<Semipath>::iterator it = bfs_path.begin();
//        for(int i = 0; i < bfs_path.size(); i++){
//            cout << stopMap[(*it).getStopid()].getCode() << " " << (*it).getName() << endl;
//            advance(it, 1);
//        }
//    }
//


//    cout << d.dijkstra_distance(235, 2119) << endl;
//    list<Semipath> dijkstra_path = d.dijkstra_path(235, 2119);
//    if(dijkstra_path.size() == 0){
//        cout << -1 << endl;
//    }
//    else{
//        list<Semipath>::iterator it = dijkstra_path.begin();
//        for(int i = 0; i < dijkstra_path.size(); i++){
//            cout << stopMap[(*it).getStopid()].getCode() << " " << (*it).getName() << endl;
//            advance(it, 1);
//        }
//    }

//    map<Stop, double> nearStopsMap = bd.nearStops(41.13, -8.6, 0.6);
//    map<Stop,double>::iterator iter;
//
//    cout << "Code" << "   " << "Distance" << endl;
//    for (iter = nearStopsMap.begin(); iter != nearStopsMap.end(); iter++) {
//        cout << iter->first.getCode() << "   " << iter->second << endl;
//    }
//


//    map<Stop, double> nearestStop = bd.nearestStop(41.13, -8.6);
//
//    map<Stop,double>::iterator it = nearestStop.begin();
//    cout << endl << endl;
//    cout << "Code" << "   " << "Distance" << endl;
//    cout << it->first.getCode() << "   " << it->second << endl;
    diaNoiteMenu(bd);
    return 0;
}
// O(|V|), where V = stops
map<string, int> reverseStops(map<int, Stop> stopMap) {
    map<int, Stop>::iterator iter;

    map<string, int> reverseStopMap;

    for (iter = stopMap.begin(); iter != stopMap.end(); iter++) {
        reverseStopMap[iter->second.getCode()] = iter->first;
    }
    return reverseStopMap;
}

//O(|V|log|V|), where v = stops
map<int, Stop> loadStops() {
    map<int, Stop> stopMap;
    ifstream stops("../dataset/stops.csv");
    if (stops.is_open()) {
        int count = 1;
        Stop stop;
        string line, code, name, zone, latitude, longitude, throwaway;
        getline(stops, throwaway);
        while(getline(stops, line)) {
            stringstream sep(line);
            getline(sep, code, ',');
            getline(sep, name, ',');
            getline(sep, zone, ',');
            getline(sep, latitude, ',');
            getline(sep, longitude, '\n');
            stop.setCode(code);
            stop.setName(name);
            stop.setZone(zone);
            stop.setLatitude(stod(latitude));
            stop.setLongitude(stod(longitude));
            stopMap[count] = stop;
            count++;
        }
        return stopMap;
    } else throw ("stops.csv file not found in dataset folder!");
}

// passar bd por parâmetro
void diaNoiteMenu(const BaseDados& bd){
    int input;
    do {
        Menu::drawEscolhaDN();
        input = Menu::getNumInput();
        switch (input) {
            case 1 :
                parCorMenu(true, bd);
                break;
            case 2 :
                parCorMenu(false, bd);
                break;
            default:
                break;
        }
    } while (input!=0);
}

void parCorMenu(bool dia, const BaseDados& bd){
    int input;
    do {
        Menu::drawEscolhaDN();
        input = Menu::getNumInput();
        switch (input) {
            case 1 :
                getTravel(dia, getParagem(true, true, bd), getParagem(true, false, bd));
                break;
            case 2 :
                getTravel(dia, getParagem(false, true, bd), getParagem(false, false, bd));
                break;
            default:
                break;
        }
    } while (input!=0);
}


int getParagem(bool paragens, bool origem, const BaseDados& bd){
    if(paragens){
        Menu::drawInputPar(origem);
        string input = Menu::getStrInput();
        cin >> input;

        map<string, int>::iterator it;
        for(it = bd.getReverseStopMap().begin(); it!=bd.getReverseStopMap().end(); it++){
            if(it->first == input){
                return it->second;
            }
        }
        return -1;
    }
    else{
        Menu::drawInputCoord(origem, true);
        double lat = Menu::getNumInput();

        Menu::drawInputCoord(origem, false);
        double lon = Menu::getNumInput();

        map<int, Stop>::iterator it;
        for(it = bd.getStopMap().begin(); it!=bd.getStopMap().end(); it++){
            if(it->second.getLongitude()-lon < 0.1 and it->second.getLatitude()-lat < 0.1){
                return it->first;
            }
        }
    }
    return -1;
}

void getTravel(bool dia, int paragem1, int paragem2){
    //algoritmo;
}
