#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

class Graph{
public:
    int n;
    std::vector<std::vector<int>> adj;

    Graph(int vertices): n(vertices), adj(n, std::vector<int>(n, 0)){};

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

    bool hasEdge(int u, int v) const {
        if (u < 0 || u >= n || v < 0 || v >= n) return false;
        return adj[u][v] == 1;
    }

    int degree(int i) const {
        if (i < 0 || i >= n) return 0;
        int ans = 0;
        for (int j = 0; j < n; ++j){
            ans += adj[i][j];
        }
        return ans;
    }

    std::vector<int> find_neighbours(int i) const {
        std::vector<int> ans;
        if (i < 0 || i >= n) return ans;
        for (int j = 0; j < n; ++j){
            if (adj[i][j] && j != i) ans.push_back(j);
        }
        return ans;
    }

    void printGraph() const {
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                std::cout << adj[i][j] << " ";
            }
            std::cout << '\n';
        }
    }

    std::vector<int> closed_neighbourhood(int v) const {
        std::vector<int> ans = find_neighbours(v);
        ans.push_back(v);
        return ans;
    }

    bool domination(int a, int b) const {
        std::vector<int> na = closed_neighbourhood(a);
        std::vector<int> nb = closed_neighbourhood(b);

        for (int v : na){
            if (std::find(nb.begin(), nb.end(), v) == nb.end()){
                return false;
            }
        }
        return true;
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

Graph delete_vert(const std::vector<int>& vertices, const Graph& g) {
    if (g.n == 0) return Graph(0);
    
    std::vector<int> remaining_vertices;
    for (int i = 0; i < g.n; ++i) {
        if (std::find(vertices.begin(), vertices.end(), i) == vertices.end()) {
            remaining_vertices.push_back(i);
        }
    }
    
    int new_n = remaining_vertices.size();
    if (new_n == 0) return Graph(0);
    
    Graph new_g(new_n);
    
    std::vector<int> old_to_new(g.n, -1);
    for (int i = 0; i < new_n; ++i) {
        old_to_new[remaining_vertices[i]] = i;
    }

    for (int i = 0; i < new_n; ++i) {
        int old_i = remaining_vertices[i];
        for (int j = i + 1; j < new_n; ++j) {
            int old_j = remaining_vertices[j];
            if (g.adj[old_i][old_j]) {
                new_g.addEdge(i, j);
            }
        }
    }
    
    return new_g;
}

int ms2(Graph g, std::vector<int> vertices);
int ms1(Graph g, std::vector<int> vertices);

int ms(Graph g){
    int n = g.n;
    
    // ИНСТРУКЦИЯ 2
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    std::vector<std::vector<int>> comps = g.findAllComps();

    // ИНСТРУКЦИЯ 1: Разложение на компоненты
    if (comps.size() > 1) {
        int minim = 10000;
        std::vector<int> smallest_comp;
        for (int i = 0; i < comps.size(); ++i){
            if (comps[i].size() < minim){
                minim = comps[i].size();
                smallest_comp = comps[i];
            }
        }
        return ms(delete_vert(smallest_comp, g)) + (smallest_comp.size() <= 2) ? 1 : ms(addition(delete_vert(smallest_comp, g)));
    }

    // ИНСТРУКЦИЯ 3: Выбор вершин A и B
    int A = -1;
    int min_degree = n + 1;
    
    for (int i = 0; i < n; ++i){
        int deg = g.degree(i);
        if (deg > 0 && deg < min_degree){
            min_degree = deg;
            A = i;
        }
    }
    
    // Если все вершины изолированы
    // if (A == -1) return n;
    
    std::vector<int> neighbours_A = g.find_neighbours(A);
    
    int B = -1;
    int max_degree = -1;
    
    for (int vert : neighbours_A){
        if (g.degree(vert) > max_degree){
            max_degree = g.degree(vert);
            B = vert;
        }
    }

    if (g.degree(A) == 1) {
        std::vector<int> to_remove = g.closed_neighbourhood(A);
        return 1 + ms(delete_vert(to_remove, g));
    }
   
    else if (g.degree(A) == 2){
        int B1 = (neighbours_A[0] == B) ? neighbours_A[1] : neighbours_A[0];
        
        // ИНСТРУКЦИЯ 4
        if (g.hasEdge(B1, B)) {
            std::vector<int> to_remove = g.closed_neighbourhood(A);
            return 1 + ms(delete_vert(to_remove, g));
        } 
        
        // Вариант 1:
        std::vector<int> to_remove1;
        auto nb1 = g.closed_neighbourhood(B);
        auto nb2 = g.closed_neighbourhood(B1);
        to_remove1.insert(to_remove1.end(), nb1.begin(), nb1.end());
        to_remove1.insert(to_remove1.end(), nb2.begin(), nb2.end());
        std::sort(to_remove1.begin(), to_remove1.end());
        to_remove1.erase(std::unique(to_remove1.begin(), to_remove1.end()), to_remove1.end());
        
        Graph g1 = delete_vert(to_remove1, g);
        int result1 = 2 + ms(g1);
        
        // Вариант 2:
        std::vector<int> to_remove2 = g.closed_neighbourhood(A);
        Graph g2 = delete_vert(to_remove2, g);
        
        // Находим N2(A)
        std::set<int> N2_A;
        for (int neighbor : neighbours_A) {
            auto neighbors_of_neighbor = g.find_neighbours(neighbor);
            for (int v : neighbors_of_neighbor) {
                if (v != A) {
                    N2_A.insert(v);
                }
            }
        }
        std::vector<int> N2_A_vec(N2_A.begin(), N2_A.end());
        
        int result2 = 1 + ms2(g2, N2_A_vec);
        
        // ИНСТРУКЦИЯ 5
        return std::max(result1, result2);
    }
    // ИНСТРУКЦИЯ 6
    else if (g.degree(A) == 3) {
        std::vector<int> to_remove = g.closed_neighbourhood(A);
        Graph g1 = delete_vert({A}, g);
        Graph g2 = delete_vert(to_remove, g);
        
        int result1 = ms2(g1, neighbours_A);
        int result2 = 1 + ms(g2);
        
        return std::max(result1, result2);
    }
 
    // else {
    //     std::vector<int> to_remove = g.closed_neighbourhood(B);
    //     Graph g1 = delete_vert({B}, g);
    //     Graph g2 = delete_vert(to_remove, g);
        
    //     int result1 = ms(g1);
    //     int result2 = 1 + ms(g2);
        
    //     return std::max(result1, result2);
    // }
}

int ms1(Graph g, std::vector<int> vertices){
    if (vertices.size() != 2) return ms(g);
    
    int i = vertices[0];
    int j = vertices[1];
    if (g.degree(i) > g.degree(j)) std::swap(i, j);
    
    // ИНСТРУКЦИЯ 9
    if (g.degree(i) <= 1) return ms(g);
    
    if (g.hasEdge(i, j)){
    	// ИНСТРУКЦИЯ 10
        if (g.degree(i) <= 3) return ms(g);
        else {
            std::vector<int> cl_neighbours_i = g.closed_neighbourhood(i);
            std::vector<int> cl_neighbours_j = g.closed_neighbourhood(j);
            // ИНСТРУКЦИЯ 11
            return std::max(ms(delete_vert(cl_neighbours_i, g)), 
                          ms(delete_vert(cl_neighbours_j, g))) + 1;
        }
    }
    // else{
    //     std::vector<int> to_remove;
    //     auto nb1 = g.closed_neighbourhood(i);
    //     auto nb2 = g.closed_neighbourhood(j);
    //     to_remove.insert(to_remove.end(), nb1.begin(), nb1.end());
    //     to_remove.insert(to_remove.end(), nb2.begin(), nb2.end());
    //     std::sort(to_remove.begin(), to_remove.end());
    //     to_remove.erase(std::unique(to_remove.begin(), to_remove.end()), to_remove.end());
        
    //     return 2 + ms(delete_vert(to_remove, g));
    // }
}

int ms2(Graph g, std::vector<int> vertices){
    if (vertices.empty()) return 0;
    if (g.n == 0) return 0;
    
    vertices.erase(std::remove_if(vertices.begin(), vertices.end(), 
        [&](int v) { return v < 0 || v >= g.n; }), vertices.end());
    
    // инструкция 17
    if (vertices.size() <= 1) return 0;
    
    std::sort(vertices.begin(), vertices.end(), [&](int a, int b) {
        return g.degree(a) < g.degree(b);
    });
    // ИНСТРУКЦИЯ 18
    if (vertices.size() == 2){
        int i = vertices[0];
        int j = vertices[1];
        
        if (g.hasEdge(i, j)) return 0;
        else {
            std::vector<int> to_remove;
            auto nb1 = g.closed_neighbourhood(i);
            auto nb2 = g.closed_neighbourhood(j);
            to_remove.insert(to_remove.end(), nb1.begin(), nb1.end());
            to_remove.insert(to_remove.end(), nb2.begin(), nb2.end());
            std::sort(to_remove.begin(), to_remove.end());
            to_remove.erase(std::unique(to_remove.begin(), to_remove.end()), to_remove.end());
            // ИНСТРУКЦИЯ 19
            return 2 + ms(delete_vert(to_remove, g));
        }
    }
    
    if (vertices.size() == 3){
        int i = vertices[0];
        int j = vertices[1];
        int k = vertices[2];
        // ИНСТРУКЦИЯ 20
        if (g.degree(i) == 0){
            std::vector<int> new_v = {j, k};
            return 1 + ms1(delete_vert({i}, g), new_v);
        }
        return ms(g); 
    }
    
    return ms(g);
}

int main(){
    Graph g(9);
    g.addEdge(0, 2);
    g.addEdge(0, 4);
    g.addEdge(0, 5);
    g.addEdge(0, 6);
    g.addEdge(1, 5);
    g.addEdge(1, 7);
    g.addEdge(1, 8);
    g.addEdge(2, 4);
    g.addEdge(2, 6);
    g.addEdge(3, 6);
    g.addEdge(3, 7);
    g.addEdge(3, 8);
    g.addEdge(4, 5);
    g.addEdge(4, 6);
    g.addEdge(5, 6);

    int result = ms(g);
    std::cout << "Answer: " << result << std::endl;
    return 0;
}