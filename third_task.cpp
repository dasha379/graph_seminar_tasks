#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <set>

// генерация произвольного неориентированного графа с заданными характеристиками:
// n - число вершин
// p - реберная плотность  (0.0 - 1.0)

class Graph{
protected:
    int n;
    double p;
    std::mt19937 gen;
public:
    std::vector<std::vector<int>> adj;
    std::vector<std::pair<int, int>> edgeList;

    Graph(int vertices, double density) : n(vertices), p(density), adj(n, std::vector<int>(n, 0)){
        generateGraph();
    }

    Graph(int vertices) : n(vertices), p(0.0), adj(n, std::vector<int>(n, 0)) {};

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

class TurGraph : public Graph{
private:
    int r;
    std::vector<std::vector<int>> partitions;
public:
    TurGraph(int vert, int part) : Graph(vert), r(part) {
        generatePartitions();
        generateTuranGraph();
    }

    void generatePartitions(){
        partitions.clear();
        partitions.resize(r);
        int n = getVertNum();
        for (int i = 0; i < n; ++i){
            int ind = i % r;
            partitions[ind].push_back(i);
        }
    }

    void generateTuranGraph(){
        edgeList.clear();
        int n = getVertNum();
        generatePartitions();

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                adj[i][j] = 0;

        for (int i = 0; i < r; ++i){
            for (int j = i + 1; j < r; ++j){
                for (const auto& u : partitions[i]){
                    for (const auto& v : partitions[j]){
                        adj[u][v] = 1;
                        adj[v][u] = 1;
                        edgeList.push_back({u, v});
                    }
                }
            }
        }
    }

    ~TurGraph(){};

};

class MoonMoserGraph : public TurGraph{
private:
    int m;
public:
    MoonMoserGraph(int m_) : TurGraph(3 * m_, m_), m(m_){};

};

int main(){
    std::cout << "=== Генерация случайного графа ===\n";
    int vertices = 8;
    double density = 0.6;

    Graph g1(vertices, density);
    g1.stats();
    g1.printGraph();
    g1.printEdges();

    std::cout << "=== генерация графа Турана ===\n";
    int v = 7;
    int r = 3;
    TurGraph tur_g(v, r);
    tur_g.Graph::printGraph();
    tur_g.Graph::printEdges();

    std::cout << "=== генерация графа Муна-Мозера ===\n";
    MoonMoserGraph gr_m(3);
    gr_m.printGraph();
}