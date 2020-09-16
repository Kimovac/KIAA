#include <iostream>
#include <vector>

using namespace std;

class Graph {
    public:
        int V;
        vector<vector<int>> adjecency_list;
        vector<bool> visited;

        Graph(int v) {
            V = v;
            adjecency_list.resize(v);
            visited.resize(v, false);
        }

        void add_edge(int u, int v) {
            adjecency_list[u].push_back(v);
        }
};

void dfs(Graph &g, int u) {
    g.visited[u] = true;

    cout << u << " ";

    for(auto v : g.adjecency_list[u]) {
        if(!g.visited[v])
            dfs(g, v);
    }
}

int main() {

    int u;
    cin >> u;

    Graph g(6);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(1, 4);
    g.add_edge(2, 3);
    g.add_edge(4, 5);

    dfs(g, u);

    return 0;
}