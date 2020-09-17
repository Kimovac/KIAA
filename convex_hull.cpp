#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Point {
	Point() {}
	Point(int x, int y) : x(x), y(y){}
	int x;
	int y;
} Point;

Point p0;

void set_extreme_point(vector<Point> &points) {
	int n = points.size();

	int index = 0;
	Point ep = points[0];
	for(int i=1; i<n; i++) {
		if(points[i].x > ep.x) {
			index = i;
			ep = points[i];
		}
		else if(points[i].x == ep.x) {
			if(points[i].y < ep.y) {
				index = i;
				ep = points[i];
			}
		}
	}

	swap(points[0], points[index]);
	p0 = points[0];
}

int orientation(const Point &a, const Point &b, const Point &c) {
	int o = ((b.y - a.y)*(c.x - b.x)) - ((b.x - a.x)*(c.y - b.y));

	if(o == 0)
		return 0;

	return ((o > 0)? 1 : 2);
}

int square_distance(const Point &a, const Point &b) {
	return abs(b.x - a.x) + abs(b.y - a.y);
}

bool point_cmp(const Point &a, const Point &b) {
	int o = orientation(p0, a, b);
	if(o == 0)
		return square_distance(p0, a) < square_distance(p0, b);

	return (o == 2) ? true : false;
}

vector<Point> find_convex_hull(vector<Point> &points) {
	int n = points.size();

	set_extreme_point(points);

	sort(points.begin()+1, points.end(), point_cmp);
	
	vector<Point> convex_hull;
	convex_hull.push_back(points[0]);
	convex_hull.push_back(points[1]);

	int m = 1;
	for(int k = 2; k<n; k++) {
		while(convex_hull.size() >= 2 && 
			orientation(convex_hull[m-1], convex_hull[m], points[k]) != 2) {
			convex_hull.pop_back();
			m--;
		}

		m++;
		convex_hull.push_back(points[k]);
	}

	return convex_hull;
}

int main() {

	int n;
	cin >> n;
	vector<Point> points(n);
	for(int i=0; i<n; i++) {
		int x, y;
		cin >> x >> y;
		points[i] = Point(x, y);
	}

	vector<Point> convex_hull = find_convex_hull(points);
	for(auto p : convex_hull) 
		cout <<  p.x << " " << p.y << "\n";

	return 0;
}