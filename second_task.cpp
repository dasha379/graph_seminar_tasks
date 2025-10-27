#include <iostream>
#include <vector>
#include <unordered_set>

// Алгоритм формирования правильного подграфа, образованного заданным множеством вершин.

class Graph{
private:
	int V; // число вершин
	std::vector<std::vector<int>> adj; // список смежности
public:
	Graph(int vertices) : V(vertices), adj(vertices) {};

	void addEdge(int u, int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	Graph getSubgraph(const std::unordered_set<int>& vertex){
		for (int v : vertex){
			if (v < 0 || v > V) throw invalid_argument("vertex " + std::to_string(v) + " does not exist in the graph!");
		}

		if (vertex.size() == V) throw invalid_argument("can not create a subgraph");

		Graph subgraph(vertex.size());

		std::vector<int> oldToNew(V, -1);
		int ind = 0;
		for (int v : vertex) oldToNew[v] = ind++;

		for (int v : vertex){
			for (int neighbour : adj[v]){
				if (vertex.count(neighbour) && v < neighbour) subgraph.addEdge(oldToNew[v], oldToNew[neighbour]);
			}
		}

		return subgraph;
	}

	void printGraph(){
		for (int i = 0; i < V; ++i){
			std::cout << "вершина " << i << " соединена с: ";
			for (int neighbour : adj[i]){
				std::cout << neighbour << " ";
			}
			std::cout << '\n';
		}
	}
};

int main(){
	int n, m; // n - число вершин, m - число ребер
	
}