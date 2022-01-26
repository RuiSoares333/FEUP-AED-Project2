#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "minHeap.h"
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <float.h>
#include "Semipath.h"

using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        double weight; // An integer weight
        string line, name;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        double dist;
        int pred;
        bool visited;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir = true;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, double weight, const string& line, string name);
    bool hasEdge(int src, int dest, double weight, string line, string name);

    double dijkstra_distance(int a, int b);
    list<Semipath> dijkstra_path(int a, int b);
    void dijkstra(int a); //distancia para o grafo inteiro

    void bfs(int v);
    double bfs_distance(int a, int b);
    list<Semipath> bfs_path(int a, int b);
    list<Semipath> get_path(list<int> path);

    Graph();
};

#endif
