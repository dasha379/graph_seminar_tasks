#include <iostream>
#include <vector>

// Алгоритм формирования правильного подграфа, образованного заданным множеством вершин.

class Graph{
public:
	int V; // число вершин
	std::vector<std::vector<int>> adj; // матрица смежности

	Graph(int vertices) : V(vertices), adj(vertices) {};

	void addEdge(int u, int v){
		adj[u][v] = 1;
		adj[v][u] = 1;
	}

	Graph getSubgraph(const std::vector<int>& vertex){
		for (int v : vertex){
			if (v < 0 || v > V) throw std::invalid_argument("vertex " + std::to_string(v) + " does not exist in the graph!");
		}

		if (vertex.size() == V) throw std::invalid_argument("can not create a subgraph");

		Graph subgraph(vertex.size());

		// std::vector<int> oldToNew(V, -1);
		// int ind = 0;
		// for (int v : vertex) oldToNew[v] = ind++;

		for (int i = 0; i < vertex.size(); ++i){
			for (int j = i + 1; j < vertex.size(); ++j){
				if (adj[vertex[i]][vertex[j]]) subgraph.addEdge(vertex[i], vertex[j]);
			}
		}

		return subgraph;
	}

	void printGraph(){
		for (int i = 0; i < V; ++i){
			for (int j = 0; j < V; ++j){
				std::cout << adj[i][j] << " ";
			}
			std::cout << '\n';
		}
	}
};

Graph addition(Graph g){
	int n = g.V;
	std::vector<std::vector<int>> m;
	Graph added(n);
	for (int i = 0; i < n; ++i){
		for (int j = i + 1; j < n; ++j){
			if (!m[i][j]) added.addEdge(i, j);
		}
	}
	return added;
}

int main(){
	// int n, m; // n - число вершин, m - число ребер
	// Graph g(n);
	// for (int i = 0; i < m; ++i){
	// 	int a, b;
	// 	std::cin >> a >> b;
	// 	g.addEdge(a, b);
	// }
	Graph g(6);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(2, 4);
	g.addEdge(3, 4);
	g.addEdge(4, 5);
	g.printGraph();
	std::cout << '\n';
	// std::vector<int> ver = {1, 3, 5};
	// Graph sub = g.getSubgraph(ver);
	// sub.printGraph();

	// Graph added = addition(g);
	// added.printGraph();
}