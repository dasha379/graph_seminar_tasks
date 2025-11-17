#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

class Graph{
public:
	int n;
	std::vector<std::vector<int>> adj;

	Graph(int verices): n(vertices), adj(n, std::vector<int>(n, 0)){};

	void addEdge(int u, int v){
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    void dfs(int vert, std::vector<bool>& visited, std::vector<int>& component){
        visited[vert] = true;
        component.push_back(vert);

        for (int i = 0; i < n; ++i){
            if (adj[vert][i] && !visited[i]) {
                dfs(i, visited, component);
            }
        }
    }

    std::vector<std::vector<int>> findAllComps(){
        std::vector<bool> visited(n, false);
        std::vector<std::vector<int>> comps;

        for (int i = 0; i < n; ++i){
            if (!visited[i]){
                std::vector<int> comp;
                dfs(i, visited, comp);
                comps.push_back(comp);
            }
        }
        return comps;
    }

};

Graph addition(Graph g){
	int n = g.n;
	
	Graph added(n);
	for (int i = 0; i < n; ++i){
		for (int j = i + 1; j < n; ++j){
			if (!g.adj[i][j]) added.addEdge(i, j);
		}
	}
	return added;
}

Graph delete_vert(std::vector<int> vertices, Graph g){
	int n = g.n;
	int m = vertices.size();
	if (n < m) throw std::invalid_argument("can not delete these vertices");
	if (n == m) throw std::invalid_argument("got an empty graph =) ");

	std::vector<int> remainig_vert;
	for (int i = 0; i < n; ++i) 
		if (std::find(vertices.begin(), vertices.end(), i) == vertices.end())
			remainig_vert.push_back(i);

	std::vector<int> oldToNew(n, -1);
	for (int i = 0; i < n - m; ++i)
		oldToNew[remainig_vert[i]] = i;

	Graph new_g(n - m);
	for (int i : remainig_vert){
		for (int j : remainig_vert){
			if (i < j && g.adj[i][j])
				new_g.addEdge(oldToNew[i], oldToNew[j]);
		}
	}
	return new_g;
}

int ms(Graph g){
	int n = g.n;
	std::vector<std::vector<int>> m_adj = g.adj;
	std::vector<std::vector<int>> comp = g.findAllComps();
	// ИНСТРУКЦИЯ 1
	if (comp.size() > 1){
		int minim = 10000;
		std::vector<int> smallest_comp;
		for (int i = 0; i < comp.size(); ++i){
			if (comp[i].size() < minim){
				minim = comp[i].size();
				smallest_comp = comp[i];
			}
		}
		return ms(delete_vert(smallest_comp, g)) + (smallest_comp.size() <= 2) ? 1 : ms(addition(delete_vert(smallest_comp, g)));
	}
	// ИНСТРУКЦИЯ 2
	if (n <= 1) return n;

	// ИНСТРУКЦИЯ 3
	int minim = 100000;
	int count = 0;
	int A;
	std::vector<int> neighbours_A;
	for (int i = 0; i < n; ++i){
		for (int j = i + 1; j < n; ++j){
			count += m_adj[i][j]; 
		}
		if (count < minim){
			minim = count;
			A = i;
			for (int j = i + 1; j < n; ++j)
				if (m_adj[i][j]) neighbours_A.push_back(j);
		}
	}
	int maxim = -1;
	int B;
	int count = 0;
	std::vector<int> neighbours_B;
	for (int i = 0; i < neighbours_A.size(); ++i){
		for (int j = 0; j < n; ++j){
			if (m_adj[neighbours_A[i]][j]) count++;
		}
		if (count > maxim){
			maxim = count;
			B = neighbours_A[i];
			for (int j = neighbours_A[i] + 1; j < n; ++j)
				if (m_adj[neighbours_A[i]][j]) neighbours_B.push_back(j);
		}
	}

	if (neighbours_A.size() == 1) {
		neighbours_A.push_back(A);
		return 1 + ms(delete_vert(neighbours_A, G));
	}
	else if (neighbours_A.size() == 2){
		std::vector<int> neighbours_B1;
		int B1 = (neighbours_A[0] == B) ? neighbours_A[1] : neighbours_A[0];
		for (int i = B1 + 1; i < n; ++i)
			if (m_adj[B1][i]) neighbours_B1.push_back(i);
		if (m_adj[B1][B]) {
			neighbours_A.push_back(A);
			return 1 + ms(delete_vert(neighbours_A, G));
		} 
		neighbours_B.push_back(B);
		neighbours_B1.push_back(B1);
		neighbours_A.push_back(A);
		std::vector<int> v_union;
		std::set_union(neighbours_B.begin(), neighbours_B.end(), 
						neighbours_B1.begin(), neighbours_B1.end(), 
						std::back_inserter(v_union));
		for (int i = 0; i < v_union.size(); ++i){
			if (v_union[i] == A){
				v_union.erase(v_union.begin() + i);
			}
		}
		std::vector<int> N2_A = v_union;
		return std::max(2 + ms(delete_vert(neighbours_B1, delete_vert(neighbours_B, g))), 1 + ms2(delete_vert(neighbours_A, g), N2_A));
	}
}