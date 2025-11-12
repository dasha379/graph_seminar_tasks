#include <iostream>
#include <vector>
#include <algorithm>

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
    // 4.1
    bool independent(int v, std::vector<int>& cur_set){
        for (int vert: cur_set){
            if (adj[v][vert]) return false;
        }
        return true;
    }

    void backtrack(int cur_vert, std::vector<int>& curSet, std::vector<int>& bestSet, int& maxSize){
        // all vertices passed
        if (cur_vert == n){
            int curSize = curSet.size();
            if (curSize > maxSize){
                maxSize = curSize;
                bestSet = curSet;
            }
            return ;
        }
        // не включаем текущую вершину
        backtrack(cur_vert+1, curSet, bestSet, maxSize);

        // включаем текущую вершину
        if (independent(cur_vert, curSet)){
            curSet.push_back(cur_vert);
            backtrack(cur_vert+1, curSet, bestSet, maxSize);
            curSet.pop_back(); // возврат
        }

    }

    std::vector<int> findMaxIndSet(){
        std::vector<int> cur_set;
        std::vector<int> best_set;
        int maxSize = 0;

        backtrack(0, cur_set, best_set, maxSize);

        return best_set;
    }
    // 4.2
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

    void printGraph() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; ++j){
                std::cout << adj[i][j] << " ";
            }
            std::cout << '\n';
        }
    }
};

void printSet(const std::vector<int>& Set){
    for (size_t i = 0; i < Set.size(); ++i) std::cout << Set[i] << " ";
}
void printComps(const std::vector<std::vector<int>> comps){
    for (size_t i = 0; i < comps.size(); ++i){
        for (auto x : comps[i]) std::cout << x << " ";
        std::cout << '\n';
    }
}

int main(){
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    
    g.printGraph();
    std::cout << '\n';
    
    std::vector<int> ans = g.findMaxIndSet();
    printSet(ans);
    std::cout << '\n';

    Graph h(7);
    h.addEdge(0, 1);
    h.addEdge(0, 2);
    h.addEdge(3, 5);
    h.addEdge(3, 4);
    
    h.printGraph();
    std::cout << '\n';

    std::vector<std::vector<int>> comps = h.findAllComps();
    printComps(comps);
}
