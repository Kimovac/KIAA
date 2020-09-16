#include <iostream>
#include <vector>
#include <queue>

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

void bfs(Graph &g, int u) {
	queue<int> nodes;
	nodes.push(u);
	g.visited[u] = true;

	int tmp;
	while(!nodes.empty()) {
		tmp = nodes.front();
		nodes.pop();

		cout << tmp << " ";

		for(auto v : g.adjecency_list[u]) {
			if(!g.visited[v]) {
				g.visited[v] = true;
				nodes.push(v);
			}
		}
	}

	cout << endl;
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

	bfs(g, u);

	return 0;
}