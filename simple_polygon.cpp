#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;

pair<int, int> bottom_left;

//function that finds orientation of three points
int points_orientation(pair<int, int> &a, pair<int, int> &b, pair<int, int> &c) {
	return ((b.second - a.second)*(c.first - b.first)) -
		   ((b.first - a.first)*(c.second - b.second));
}

//fucntion that finds square distance from two points
int points_distance(pair<int, int> &a, pair<int, int> &b) {
	return (b.first - a.first)*(b.first - a.first) + 
		   (b.second - a.second)*(b.second - a.second);
}

//sort function for simple polygon
bool point_cmp(pair<int, int> a, pair<int, int> b) {
	int orientation = points_orientation(bottom_left, a, b);
	if(orientation == 0)
		return points_distance(bottom_left, a) < points_distance(bottom_left, b);

	return (orientation == 2)? true : false;
}

int main() {

	vector<pair<int, int>> points;
	points.push_back(make_pair(0, 3));
	points.push_back(make_pair(1, 1));
	points.push_back(make_pair(2, 2));
	points.push_back(make_pair(3, 3));
	points.push_back(make_pair(4, 4));
	points.push_back(make_pair(0, 0));
	points.push_back(make_pair(1, 2));
	points.push_back(make_pair(3, 1));

	int n = points.size();
	bottom_left = points[0];
	for(int i=1; i<n; i++) {
		if(points[i].second < bottom_left.second)
			bottom_left = points[i];

		if(points[i].second == bottom_left.second && 
			points[i].first < bottom_left.first) {
			bottom_left = points[i];
		}
	}
	sort(points.begin(), points.end(), point_cmp);

	for(auto &p : points) {
		cout << p.first << " " << p.second << endl;
	}


	return 0;
}