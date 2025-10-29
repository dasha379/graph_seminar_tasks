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
        std::random_device rd;
        gen.seed(rd()); // получаем случайную последовательность чисел
        std::uniform_real_distribution<> dis(0.0, 1.0);

        edgeList.clear();
        for (int i = 0; i < n; ++i){
            for (int j = i + 1; j < n; ++j){
                if (dis(gen) <= p){
                    adj[i][j] = 1;
                    adj[j][i] = 1;
                    edgeList.push_back({i, j});
                }
            }
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

    ~Graph(){};

};

int main(){
    
}