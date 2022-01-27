#include "graph.h"
#include "minHeap.h"
#include <climits>
#include <utility>

/// Construtor
/// Inicializa o grafo com o número máximo de paragens num
/// \param num int, número máximo de paragens guardadas no grafo
Graph::Graph(int num) : n(num), nodes(num+1) {
}
/// Adiciona uma edge ao grafo que vai de src até dest com direção
/// \param src int, id da paragem de origem da edge
/// \param dest int, id da paragem de destino da edge
/// \param weight double, distancia em kilometros entre as paragens src e dest
/// \param line string, código da linha que conecta as duas paragens
/// \param name string, nome da linha que conecta as duas paragens
/// Complexidade Temporal: O(log|E|), where E = edge(stop -> stop)
void Graph::addEdge(int src, int dest, double weight, const string& line, string name) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    if(hasEdge(src, dest, weight, line, name)) return;
    nodes[src].adj.push_back({dest, weight, line, name});
}

/// Calcula e retorna a distancia (double) em Kilometros entre as paragens a e b, usando o algoritmo de Dijkstra
/// \param a int, id da paragem de origem
/// \param b int, id da paragem de destino
/// Complexidade Temportal: O(|E|log|V|), where V = stop, E = edge(stop -> stop)
double Graph::dijkstra_distance(int a, int b) {
    dijkstra(a);
    if(nodes[b].dist == DBL_MAX) return -1;
    double dist = nodes[b].dist;
    return dist;
}
/// Calcula e retorna o caminho (List<Semipath>) entre as paragens a e b, usando o algoritmo de Dijkstra
/// \param a int, id da paragem de origem
/// \param b int, id da paragem de destino
/// Complexidade Temporal: O(|E|log|V|), where V = stop, E = edge(stop -> stop)
list<Semipath> Graph::dijkstra_path(int a, int b) {
    list<int> path;
    list <Semipath> ret;
    dijkstra(a);
    if(nodes[b].dist == DBL_MAX) return ret;
    int pred = nodes[b].pred;
    while(pred != a){
        path.push_front(pred);
        pred = nodes[pred].pred;
    }
    path.push_front(a);
    path.push_back(b);

    return get_path(path);
}
/// Algoritmo de Dijkstra que atribui, a todas as paragens do grafo, a distância (double), em Kilometros, até á paragem 'a' e a paragem precedente até à paragem 'a'
/// \param a int, id da paragem de origem
/// Complexidade Temporal: O(|E|log|V|), where V = stop, E = edge(stop -> stop)
void Graph::dijkstra(int a) {
    for (int v=1; v<=n; v++){
        nodes[v].visited = false;
        nodes[v].dist = DBL_MAX;
    }
    nodes[a].dist = 0;
    nodes[a].pred = a;

    MinHeap<int, double> heap(n, -1);
    for(int i = 1; i <= n; i++) heap.insert(i, nodes[i].dist);

    while(heap.getSize() > 0){
        int min = heap.removeMin();
        nodes[min].visited = true;
        if(nodes[min].dist == DBL_MAX) continue;

        for(const Edge& edge: nodes[min].adj){
            int dest = edge.dest;
            double weight = edge.weight;
            if(!nodes[dest].visited && nodes[min].dist + weight < nodes[dest].dist){
                nodes[dest].dist = nodes[min].dist + weight;
                nodes[dest].pred = min;
                heap.decreaseKey(dest, nodes[dest].dist);
            }
        }
    }
}

/// Algoritmo de Pesquisa em Largura (BFS) que atribui, a todas as paragens do grafo, a distância (double), em número de paragens, até á paragem 'a' e a paragem precedente até à paragem 'a'
/// \param a int, id da paragem de origem
/// Complexidade Temporal: O(|E|), where E = edge(stop -> stop)
void Graph::bfs(int v) {
    for (int v=1; v<=n; v++) {
        nodes[v].visited = false;
        nodes[v].dist = DBL_MAX;
        nodes[v].pred = -1;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].dist = 0;
    nodes[v].pred = v;
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        //cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist+1;
                nodes[w].pred = u;
            }
        }
    }
}

/// Calcula e retorna a distancia (double), em número de paragens, entre as paragens a e b, usando o algoritmo BFS
/// \param a int, id da paragem de origem
/// \param b int, id da paragem de destino
/// Complexidade Temporal: O(|E|), where E = edge(stop -> stop)
double Graph::bfs_distance(int a, int b) {
    if(a==b) return 0;
    bfs(a);
    if(nodes[b].dist == DBL_MAX) return -1;
    return nodes[b].dist;
}

/// Calcula e retorna o caminho (List<Semipath>) entre as paragens a e b, usando o algoritmo BFS
/// \param a int, id da paragem de origem
/// \param b int, id da paragem de destino
/// Complexidade Temporal: O(|E|), where E = edge(stop -> stop)
list<Semipath> Graph::bfs_path(int a, int b){
    bfs(a);
    list<int> path;
    list <Semipath> ret;
    if(nodes[b].dist == DBL_MAX) return ret;
    int pred = nodes[b].pred;
    while(pred != a) {
        path.push_front(pred);
        pred = nodes[pred].pred;
    }
    path.push_front(a);
    path.push_back(b);

    return get_path(path);
}

/// Verifica se a edge (src -> dest) já existe
/// Retorna True caso exista, False caso contrário
/// \param src int, id da paragem de origem da edge
/// \param dest int, id da paragem de destino da edge
/// \param weight double, distancia em Kilometros entre as duas paragens
/// \param line string, código da linha que liga as duas paragens
/// \param name string, nome da linha que liga as duas paragens
/// Complexidade Temporal: O(log|E|), where E = edge(stop -> stop)
bool Graph::hasEdge(int src, int dest, double weight, string line, string name) {
    for(auto edge:nodes[src].adj){
        if(edge.dest == dest && edge.weight == weight && edge.line == line) return true;
    }
    return false;
}

/// Converte uma lista de ids de paragens para uma lista de semipaths, para facilitar a escrita do caminho no terminal
/// Semipaths guardam o id da paragem de origem, o código e nome da linha que conecta a paragem com a seguinte
/// \param path list<int>, lista de paragens que representa o caminho. Deve ser gerada por bfs_path() ou dijkstra_path()
/// Complexidade Temporal: O(log|V|*log|E|), where V = stops, E = edge(stop -> stop)
list<Semipath> Graph::get_path(list<int> path){
    list <Semipath> ret;
    int stopid, nextid;

    stopid = path.front();
    path.pop_front();
    while(path.size() >= 1){
        nextid = path.front();
        path.pop_front();

        for(auto edge: nodes[stopid].adj){
            if(edge.dest == nextid){
                ret.push_back(Semipath(stopid, edge.line, edge.name));
                break;
            }
        }
        stopid = nextid;
    }
    ret.push_back(Semipath(stopid, "", ""));
    return ret;
}
/// Construtor Default, vazio
Graph::Graph() {}
