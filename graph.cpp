// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#include "graph.h"
#include "minHeap.h"
#include <climits>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}


// ----------------------------------------------------------
// 1) Algoritmo de Dijkstra e caminhos mais curtos
// ----------------------------------------------------------

// ..............................
// a) Distância entre dois nós
// TODO
int Graph::dijkstra_distance(int a, int b) {
    dijkstra(a);
    if(nodes[b].dist >= INT32_MA/2) return -1;
    int dist = nodes[b].dist;
    return dist;
}

// ..............................
// b) Caminho mais curto entre dois nós
// TODO
list<int> Graph::dijkstra_path(int a, int b) {
    list<int> path;
    dijkstra(a);
    if(nodes[b].dist >= INT32_MAX/2) return path;
    int pred = nodes[b].pred;
    while(pred != a){
        cout << pred << endl;
        path.push_front(pred);
        pred = nodes[pred].pred;
    }
    path.push_front(a);
    path.push_back(b);
    return path;
}

void Graph::dijkstra(int a) {
    for (int v=1; v<=n; v++){
        nodes[v].visited = false;
        nodes[v].dist = INT32_MAX/2;
    }
    nodes[a].dist = 0;
    nodes[a].pred = a;

    MinHeap<int, int> heap(n, -1);
    for(int i = 1; i <= n; i++) heap.insert(i, nodes[i].dist);

    while(heap.getSize() > 0){
        int min = heap.removeMin();
        nodes[min].visited = true;
        if(nodes[min].dist >= INT32_MAX) continue;

        for(Edge edge: nodes[min].adj){
            int dest = edge.dest;
            int weight = edge.weight;
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
        nodes[v].dist = INT32_MAX/2;
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

int Graph::bfs_distance(int a, int b) {
    if(a==b) return 0;
    bfs(a);
    if(nodes[b].dist == INT32_MAX/2) return -1;
    return nodes[b].dist;
}

list<int> Graph::bfs_path(int a, int b){
    bfs(a);
    list<int> path;

    int pred = nodes[b].pred;
    while(pred != a) {
        path.push_front(pred);
        pred = nodes[pred].pred;
    }
    path.push_front(a);
    path.push_back(b);
    return path;
}