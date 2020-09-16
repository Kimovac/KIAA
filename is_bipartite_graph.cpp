#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
	public:
		int V;
		vector<vector<int>> adjecency_list;
		vector<bool> visited;
		vector<int> color;

		Graph(int v) {
			V = v;
			adjecency_list.resize(v);
			visited.resize(v, false);
			color.resize(v, -1);
		}

		void add_edge(int u, int v) {
			adjecency_list[u].push_back(v);
			adjecency_list[v].push_back(u);
		}
};

bool is_bipartite_graph(Graph &g) {
	g.visited[0] = true;
	g.color[0] = 0;

	queue<int> nodes;
	nodes.push(0);

	int tmp;
	while(!nodes.empty()) {
		tmp = nodes.front();
		nodes.pop();
		for(auto v : g.adjecency_list[tmp]) {
			if(g.color[v] == g.color[tmp])
				return false;

			if(!g.visited[v]) {
				g.color[v] = !g.color[tmp];
				g.visited[v] = true;
				nodes.push(v);
			}
		}
	}

	return true;
}

void print_bipartite_graph(const Graph &g) {
	vector<int> nodes1;
	vector<int> nodes2;

	for(int i=0; i<g.V; i++) {
		if(g.color[i])
			nodes2.push_back(i);
		else
			nodes1.push_back(i);
	}

	cout << "group 1: ";
	for(auto x : nodes1)
		cout << x << " ";
	cout << endl;

	cout << "group 2: ";
	for(auto x : nodes2)
		cout << x << " ";
	cout << endl;
}


int main() {

	Graph g(6);
	g.add_edge(0, 1);
	g.add_edge(1, 2);
	g.add_edge(2, 3);
	g.add_edge(3, 4);
	g.add_edge(4, 5);
	g.add_edge(5, 0);

	bool is_bipartite = is_bipartite_graph(g);
	cout << (is_bipartite? "True" : "False") << endl;
	if(is_bipartite)
		print_bipartite_graph(g);

	return 0;
}