#include <algorithm>
#include <iostream>
#include "Menu.h"
#include <map>
#include "BaseDados.h"

using namespace std;

void diaNoiteMenu(const BaseDados& bd);
void parCorMenu(bool dia, const BaseDados& bd);
void getTravel(bool dia, int paragem1, int paragem2, BaseDados bd, double dist1, double dist2);
int getParagem(bool paragens, bool origem, BaseDados bd);
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

    //Menu
    diaNoiteMenu(bd);
    return 0;
}

/// Cria um mapa com as keys sendo o código de uma paragem e os values sendo o id correspondente a essa paragem
/// \param stopMap mapa com as keys sendo o id de uma paragem e os values sendo a paragem correspondente
/// Complexidade temporal: O(|V|), where V = stops
map<string, int> reverseStops(map<int, Stop> stopMap) {
    map<int, Stop>::iterator iter;

    map<string, int> reverseStopMap;

    for (iter = stopMap.begin(); iter != stopMap.end(); iter++) {
        reverseStopMap[iter->second.getCode()] = iter->first;
    }
    return reverseStopMap;
}

/// Lê as stops do ficheiro stops.csv e adiciona-as ao mapa stopMap, com as keys sendo o id de uma paragem, atribuído por auto-increment, e os values sendo a paragem correspondente
/// Complexidade temporal: O(|V|log|V|), where v = stops
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
    int input, origem, destino;
    do {
        Menu::drawEscolhaParCor();
        input = Menu::getNumInput();
        switch (input) {
            case 1 :
                origem = getParagem(true, true, bd);
                destino = getParagem(true, false, bd);
                getTravel(dia, origem, destino, bd, 1, 1);
                break;
            case 2 :
                origem = getParagem(false, true, bd);
                destino = getParagem(false, false, bd);
                getTravel(dia, origem , destino, bd, 1, 1);
                break;
            default:
                exit(0);
                break;
        }
    } while (input!=0);
}


int getParagem(bool paragens, bool origem, BaseDados bd){
    if(paragens){
        Menu::drawInputPar(origem);
        string input = Menu::getStrInput();

        return bd.getReverseStopMap()[input];
    }
    else{
        Menu::drawInputCoord(origem, true);
        double lat = Menu::getDoubleInput();

        Menu::drawInputCoord(origem, false);
        double lon = Menu::getDoubleInput();

        Menu::drawEscolhaCor();
        int input = Menu::getNumInput();
        switch (input) {
            case 1 :{
                map<Stop, double> proxima = bd.nearestStop(lat, lon);
                map<Stop, double>::iterator it = proxima.begin();
                return bd.getReverseStopMap()[(*it).first.getCode()];
                break;
            }
            case 2 :{
                double raio;
                int count = 1;
                map<string, int> reverse = bd.getReverseStopMap();
                cout << "Qual o raio que esta disponivel a andar? (m)" << endl;
                cin >> raio;
                raio = raio / 1000;
                map<Stop, double> proximas = bd.nearStops(lat, lon, raio);
                cout << proximas.size() << endl;
                for(auto pair : proximas){
                    cout << count << " - ";
                    cout << pair.first.getCode() << " - " << pair.second << " km" << endl;
                    count++;
                }

                auto ite = proximas.begin();
                auto ite2 = proximas.begin();
//                for (int i = 1; i <= proximas.size(); i++){
//                    cout << i << " - " << reverse[(*ite).first.getCode()] << " - " << (*ite).second << endl;
//                    cout << 1 << endl;
//                    advance(ite, 1);
//                }
                cout << "Escolha a paragem desejada" << endl;
                int inp;
                cin >> inp;
                inp--;
                advance(ite2, inp);
                return reverse[(*ite2).first.getCode()];
                break;}
            default:
                break;
        }
    }
    return -1;
}

void getTravel(bool dia, int paragem1, int paragem2, BaseDados bd, double dist1, double dist2){
    bool pe, bfs;
    int escpe, escca;
    Graph graph;
    list<Semipath> path;
    map<int, Stop> stopmap = bd.getStopMap();
    //quer poder andar a pe?
    Menu::drawEscolhaPe();
    escpe = Menu::getNumInput();
    switch(escpe){
        case 2:
            pe=false;
            break;
        default:
            pe=true;
            break;
    }

    Menu::drawEscolhaTipoCam();
    escca = Menu::getNumInput();
    switch(escca){
        case 1 :
            bfs = true;
            break;
        case 2:
            bfs = false;
            break;
    }

    //desenha o caminho
    if(pe && bfs){ //andar a pe e caminho com menos paragens
        if(dia){
            graph = bd.getPdGraph();
            Semipath last;
            cout << "Numero de Paragens: " << int(graph.bfs_distance(paragem1, paragem2)) << endl;
            path = graph.bfs_path(paragem1, paragem2);
            //TODO dizer a distancia a andar a pe
            for(Semipath semi : path){
                cout << stopmap[semi.getStopid()].getCode() << " | " << stopmap[semi.getStopid()].getName() << " | " << stopmap[semi.getStopid()].getZone() << endl;
                if(semi.getName() != "") cout << "   |\n   || " << semi.getLine() << " | " << semi.getName() << "\n   |" << endl;
                last = semi;
            }
            cout << last.getName() << endl;
            cout << endl << endl;
        }
        else{
            graph = bd.getPmGraph();
            Semipath last;
            cout << "Numero de Paragens: " << int(graph.bfs_distance(paragem1, paragem2)) << endl;
            path = graph.bfs_path(paragem1, paragem2);
            //TODO dizer a distancia a andar a pe
            for(Semipath semi : path){
                cout << stopmap[semi.getStopid()].getCode() << " | " << stopmap[semi.getStopid()].getName() << " | " << stopmap[semi.getStopid()].getZone() << endl;
                if(semi.getName() != "") cout << "   |\n   || " << semi.getLine() << " | " << semi.getName() << "\n   |" << endl;
                last = semi;
            }
            cout << last.getName() << endl;
            cout << endl << endl;
        }
    }
    else if(pe && !bfs) {//andar a pe e caminho com menor distancia
        if(dia){
            graph = bd.getPdGraph();
            Semipath last;
            cout << "Distancia: " << graph.dijkstra_distance(paragem1, paragem2) << " Km" << endl;
            path = graph.dijkstra_path(paragem1, paragem2);
            //TODO dizer a distancia a andar a pe
            for(Semipath semi : path){
                cout << stopmap[semi.getStopid()].getCode() << " | " << stopmap[semi.getStopid()].getName() << " | " << stopmap[semi.getStopid()].getZone() << endl;
                if(semi.getName() != "") cout << "   ||\n   || " << semi.getLine() << " | " << semi.getName() << "\n   ||" << endl;
                last = semi;
            }
            cout << last.getName() << endl;
            cout << endl << endl;
        }
        else{
            graph = bd.getPmGraph();
            Semipath last;
            cout << "Distancia: " << graph.dijkstra_distance(paragem1, paragem2) << " Km" << endl;
            path = graph.dijkstra_path(paragem1, paragem2);
            //TODO dizer a distancia a andar a pe
            for(Semipath semi : path){
                cout << stopmap[semi.getStopid()].getCode() << " | " << stopmap[semi.getStopid()].getName() << " | " << stopmap[semi.getStopid()].getZone() << endl;
                if(semi.getName() != "") cout << "   ||\n   || " << semi.getLine() << " | " << semi.getName() << "\n   ||" << endl;
                last = semi;
            }
            cout << last.getName() << endl;
            cout << endl << endl;
        }
    }
    else if (!pe && bfs){ //nao andar a pe e caminho com menos paragens
        if(dia){
            graph = bd.getDGraph();
            Semipath last;
            cout << "Numero de Paragens: " << int(graph.bfs_distance(paragem1, paragem2)) << endl;
            path = graph.bfs_path(paragem1, paragem2);
            for(Semipath semi : path){
                cout << stopmap[semi.getStopid()].getCode() << " | " << stopmap[semi.getStopid()].getName() << " | " << stopmap[semi.getStopid()].getZone() << endl;
                if(semi.getName() != "") cout << "   ||\n   || " << semi.getLine() << " | " << semi.getName() << "\n   ||" << endl;
                last = semi;
            }
            cout << last.getName() << endl;
            cout << endl << endl;
        }
        else{
            graph = bd.getMGraph();
            Semipath last;
            cout << "Numero de Paragens: " << int(graph.bfs_distance(paragem1, paragem2)) << endl;
            path = graph.bfs_path(paragem1, paragem2);
            for(Semipath semi : path){
                cout << stopmap[semi.getStopid()].getCode() << " | " << stopmap[semi.getStopid()].getName() << " | " << stopmap[semi.getStopid()].getZone() << endl;
                if(semi.getName() != "") cout << "   ||\n   || " << semi.getLine() << " | " << semi.getName() << "\n   ||" << endl;
                last = semi;
            }
            cout << last.getName() << endl;
            cout << endl << endl;
        }
    }
    else{ //nao andar a pe e caminho com menor distancia
        if(dia){
            graph = bd.getDGraph();
            Semipath last;
            cout << "Distancia: " << graph.dijkstra_distance(paragem1, paragem2) << " Km" << endl;
            path = graph.dijkstra_path(paragem1, paragem2);
            for(Semipath semi : path){
                cout << stopmap[semi.getStopid()].getCode() << " | " << stopmap[semi.getStopid()].getName() << " | " << stopmap[semi.getStopid()].getZone() << endl;
                if(semi.getName() != "") cout << "   ||\n   || " << semi.getLine() << " | " << semi.getName() << "\n   ||" << endl;
                last = semi;
            }
            cout << last.getName() << endl;
            cout << endl << endl;
        }
        else{
            graph = bd.getMGraph();
            Semipath last;
            cout << "Distancia: " << graph.dijkstra_distance(paragem1, paragem2) << " Km" << endl;
            path = graph.dijkstra_path(paragem1, paragem2);
            for(Semipath semi : path){
                cout << stopmap[semi.getStopid()].getCode() << " | " << stopmap[semi.getStopid()].getName() << " | " << stopmap[semi.getStopid()].getZone() << endl;
                if(semi.getName() != "") cout << "   ||\n   || " << semi.getLine() << " | " << semi.getName() << "\n   ||" << endl;
                last = semi;
            }
            cout << last.getName() << endl;
            cout << endl << endl;
        }
    }
}
