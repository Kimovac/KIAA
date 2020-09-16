#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;


class Graph {
	public:
		int V;
		vector<vector<pair<int, int>>> adjecency_list;
		vector<int> distances; 
		vector<bool> path_found;

		Graph(int v) {
			V = v;
			adjecency_list.resize(v);
			distances.resize(v, numeric_limits<int>::max());
			path_found.resize(v, false);
		}

		void add_edge(int u, int v, int w) {
			adjecency_list[u].push_back(make_pair(v, w));
			adjecency_list[v].push_back(make_pair(u, w));
		}
};



void dijkstra(Graph &g, int u, int v) {
	auto heap_cmp = [](pair<int, int> l, pair<int, int> r){ return l.second > r.second; };
	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(heap_cmp)> heap(heap_cmp);

	g.distances[u] = 0;
	//					i, 		d(u, i)
	heap.push(make_pair(u, g.distances[u]));

	pair<int, int> tmp;
	while(!heap.empty()) {
		tmp = heap.top();
		heap.pop();

		if(g.path_found[tmp.first])
			continue;

		g.path_found[tmp.first] = true;

		for(const auto &p : g.adjecency_list[tmp.first]) {
			//       d(u, tmp)    +     d(tmp, p)    <    d(u, p)
			if(g.distances[tmp.first] + p.second < g.distances[p.first]) {
				//	   d(u, p)       =       d(u, tmp)    +     d(tmp,p) 
				g.distances[p.first] = g.distances[tmp.first] + p.second;
			}

			heap.push(make_pair(p.first, g.distances[p.first]));
		}
	}

	cout << "d(u, v) = " << g.distances[v] << endl;
}

int main() {
	Graph g(9);
	g.add_edge(0, 1, 4);
	g.add_edge(0, 7, 8);
  	g.add_edge(1, 7, 11);
  	g.add_edge(1, 2, 8);
  	g.add_edge(2, 8, 2);
  	g.add_edge(2, 3, 7);
  	g.add_edge(7, 8, 7);
  	g.add_edge(7, 6, 1);
  	g.add_edge(8, 6, 6);
  	g.add_edge(2, 5, 4);
  	g.add_edge(6, 5, 2);
  	g.add_edge(3, 5, 14);
  	g.add_edge(3, 4, 9);
  	g.add_edge(4, 5, 10);

  	dijkstra(g, 0, 4);

  	return 0;
}