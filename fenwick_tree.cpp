#include <iostream>
#include <vector>

using namespace std;

int query(vector<int> &tree, int i) {
	int s = 0;
	for(i++; i > 0; i -= i & -i)
		s += tree[i];
	return s;
}

int query(vector<int> &tree, int a, int b) {
	return query(tree, b) - query(tree, a - 1);
}

void update(vector<int> &tree, int i, int x) {
	for(i++; i < tree.size(); i += i & -i)
		tree[i] += x;
}

int main() {

	int n;
	cin >> n;

	vector<int> v(n);
	vector<int> tree(n + 1);

	while(true) {
		string cmd;
		int x, y;
		cin >> cmd >> x >> y;
		if(cmd == "get")
			cout << query(tree, x, y) << '\n';
		else if(cmd == "add") {
			update(tree, x, y);
			v[x] += y;
			for(int x : v)
				cout << x << ' ';
			cout << '\n';
		}
		else
			break;
	}

	return 0;
}
