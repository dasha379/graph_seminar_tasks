#include <iostream>
#include <vector>

// backtraking algorithm для нахождения наибольшего независимого множества вершин в графе

class Graph{
private:
    int n;
    std::vector<std::vector<int>> adj;
public:
    Graph(int vertices) : n(vertices), adj(n, std::vector<int>(n, 0)){

    }

    void addEdge(int u, int v){
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    bool independent(int v, std::vector<int> cur_set){
        for (int vert: cur_set){
            if (adj[v][vert]) return false;
        }
        return true;
    }

    void max_independent_set(std::vector<int>& cur_set, std::vector<int>& max_set, int vert){}
};
