#include "graph.h"
#include "minHeap.h"
#include <climits>
#include <utility>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num) : n(num), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, double weight, const string& line, string name) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    if(hasEdge(src, dest, weight, line, name)) return;
    nodes[src].adj.push_back({dest, weight, line, name});
//    if (!hasDir) nodes[dest].adj.push_back({src, weight, line});
}


// ----------------------------------------------------------
// 1) Algoritmo de Dijkstra e caminhos mais curtos
// ----------------------------------------------------------

// ..............................
// a) Distância entre dois nós
// TODO
double Graph::dijkstra_distance(int a, int b) {
    dijkstra(a);
    if(nodes[b].dist == DBL_MAX) return -1;
    double dist = nodes[b].dist;
    return dist;
}

// ..............................
// b) Caminho mais curto entre dois nós
// TODO
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
// Depth-First Search: example implementation
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

double Graph::bfs_distance(int a, int b) {
    if(a==b) return 0;
    bfs(a);
    if(nodes[b].dist == DBL_MAX) return -1;
    return nodes[b].dist;
}

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

bool Graph::hasEdge(int src, int dest, double weight, string line, string name) {
    for(auto edge:nodes[src].adj){
        if(edge.dest == dest && edge.weight == weight && edge.line == line) return true;
    }
    return false;
}


list<Semipath> Graph::get_path(list<int> path){
    list <Semipath> ret;
    int stopid, nextid;

    stopid = path.front();
    path.pop_front();
    while(path.size() > 1){
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