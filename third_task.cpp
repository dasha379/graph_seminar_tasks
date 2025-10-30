#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

// генерация произвольного неориентированного графа с заданными характеристиками:
// n - число вершин
// p - реберная плотность  (0.0 - 1.0)

class Graph{
private:
    int n;
    double p;
    std::vector<std::vector<int>> adj;
    std::vector<std::pair<int, int>> edgeList;
    std::mt19937 gen;
public:

    Graph(int vertices, double density) : n(vertices), p(density), adj(n, std::vector<int>(n, 0)){
        generateGraph();
    }

    void generateGraph(){
        edgeList.clear();

        int maxPosEdges = n * (n - 1) / 2;
        int edges = static_cast<int>(p * maxPosEdges);
        std::vector<std::pair<int, int>> allEdges;
        for (int i = 0; i < n; ++i){
            for (int j = i + 1; j < n; ++j){
                allEdges.push_back({i, j});
            }
        }
        std::random_device rd;
        gen.seed(rd()); // получаем случайную последовательность чисел
        std::shuffle(allEdges.begin(), allEdges.end(), gen); // reorders the elements

        for (int i = 0; i < edges; ++i){
            int u = allEdges[i].first;
            int v = allEdges[i].second;

            adj[u][v] = 1;
            adj[v][u] = 1;
            edgeList.push_back({u, v});
        }
    }

    void printGraph(){
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				std::cout << adj[i][j] << " ";
			}
			std::cout << '\n';
		}
	}

    void printEdges(){
        std::cout << "edge list\n";
        for (const auto& edge: edgeList) std::cout << edge.first << " " << edge.second << '\n';
    }

    void stats(){
        int maxPosEdges = n * (n - 1) / 2;
        int realEdges = edgeList.size();
        double actual_density = static_cast<double>(realEdges) / maxPosEdges;
        std::cout << "amount of verices: " << n << '\n';
        std::cout << "amount of edges: " << realEdges << '\n';
        std::cout << "the density we got: " << actual_density << '\n';
    }

    const std::vector<std::vector<int>>& getAdj() const{
        return adj;
    }

    const std::vector<std::pair<int, int>>& getEdgeList() const {
        return edgeList;
    }

    int getVertNum() const {
        return n;
    }

    int getEdgeAmount() const {
        return edgeList.size();
    }

    ~Graph(){};

};

int main(){
    std::cout << "=== Генерация случайного графа ===\n";
    int vertices = 8;
    double density = 0.6;
    
    Graph g1(vertices, density);
    g1.stats();
    g1.printGraph();
    g1.printEdges();
}