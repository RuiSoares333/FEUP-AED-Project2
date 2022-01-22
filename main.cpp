#include <iostream>
#include <fstream>
#include "Menu.h"
#include <map>
#include <sstream>
#include "BaseDados.h"
#include "graph.h"
#include "Stop.h"

using namespace std;

void mainMenu();
void parCorMenu(bool dia);
void getTravel(bool dia, string paragem);
void getTravel(bool dia, string paragem1, string paragem2);
string getParagem(bool paragens, bool origem);
map<int, Stop> loadStops();

int main() {
    map<int, Stop> stopMap = loadStops();
    Graph dGraph(stopMap.size(), true);
    Graph mGraph(stopMap.size(), true);
    BaseDados bd(dGraph, mGraph, stopMap);
    bd.loadAllLines();

    cout << bd.getDGraph().bfs_distance(1,4) << endl;
    cout << bd.getDGraph().dijkstra_distance(1,4) << endl;

    return 0;
}

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
/*
void diaNoiteMenu(){
    int input = -1;
    do {
        Menu::drawEscolhaDN();
        input = Menu::getNumInput();
        switch (input) {
            case 1 :
                parCorMenu(true);
                break;
            case 2 :
                parCorMenu(false);
                break;
            default:
                break;
        }
    } while (input!=0);
}

void parCorMenu(bool dia){
    int input = -1;
    do {
        Menu::drawEscolhaDN();
        input = Menu::getNumInput();
        switch (input) {
            case 1 :
                getTravel(dia, getParagem(true));
                break;
            case 2 :
                getTravel(dia, getParagem(false));
                break;
            default:
                break;
        }
    } while (input!=0);
}


string getParagem(bool paragens, bool origem){

    if(paragens){
        if(origem){

        }
        cout << "--- Indique o Nome da Paragem de Origem ---" << endl;
        cout << "Origem: ";
        cout << "--- Indique o Nome da Paragem de Destino ---" << endl;
        cout << "Destino: "
    }
    else{
        cout << "--- Indique as Coordenadas de Origem ---" << endl;
        cout << "Origem: ";
        cout << "--- Indique as Coordenadas de Destino ---" << endl;
        cout << "Destino: "
    }
}

void getTravel(bool dia, string paragem1, string paragem2){
    //algoritmo;
}
 */