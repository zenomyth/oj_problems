#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
	int x;
	int y;
	int n;
};

int coordinate_less_than(const Point &a, const Point &b)
{
	if (a.x == b.x && a.y == b.y)
		return a.n < b.n;
	return a.y == b.y ? a.x < b.x : a.y < b.y;
}

class AngleLessThan {
	private:
	Point m;
	public:
	AngleLessThan(const Point &p) : m(p) {}
	bool operator() (Point a, Point b) {
		if (a.x == b.x && a.y == b.y)
			return a.n < b.n;
		int64_t ax = a.x - m.x;
		int64_t ay = a.y - m.y;
		int64_t bx = b.x - m.x;
		int64_t by = b.y - m.y;
		if (ax == 0 && ay == 0)
			return true;
		if (bx == 0 && by == 0)
			return false;
		int sax = ax > 0 ? 1 : -1;
		int sbx = bx > 0 ? 1 : -1;
		int64_t cosa = sax * ax * ax * (bx * bx + by * by);
		int64_t cosb = sbx * bx * bx * (ax * ax + ay * ay);
		return cosa == cosb ? ax < bx : cosb < cosa;
	}
};

void print_vector(const vector<Point> &points)
{
	for (vector<Point>::const_iterator it = points.begin(); it != points.end(); ++it)
		cout << "(" << it->n << ", " << it->x << ", " << it->y << "); ";
	cout << endl;
}

bool point_equal(const Point &a, const Point &b)
{
	if (a.x == b.x && a.y == b.y)
		return true;
	return false;
}

int64_t cross_product(const Point &p1, const Point &p2, const Point &p3)
{
	return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

double dist(const Point &p1, const Point &p2)
{
	double x = p2.x - p1.x;
	double y = p2.y - p1.y;
	return sqrt(x * x + y * y);
}

void graham_scan(vector<Point> &points)
{
	// print_vector(points);
	vector<Point>::iterator it_m = min_element(points.begin(), points.end(), coordinate_less_than);
	// cout << "min = (" << it_m->n << ", " << it_m->x << ", " << it_m->y << ")" << endl;
	AngleLessThan angel_less_than(*it_m);
	stable_sort(points.begin(), points.end(), angel_less_than);
	// print_vector(points);
	points.erase(unique(points.begin(), points.end(), point_equal), points.end());
	// print_vector(points);
	vector<Point> ch;
	for (vector<Point>::iterator it = points.begin(); it != points.end(); ++it) {
		if (ch.size() < 2) {
			ch.push_back(*it);
			continue;
		}
		int64_t cp = cross_product(ch[ch.size() - 2], ch[ch.size() - 1], *it);
		while (cp <= 0) {
			ch.pop_back();
			if (ch.size() < 2)
				break;
			cp = cross_product(ch[ch.size() - 2], ch[ch.size() - 1], *it);
		}
		ch.push_back(*it);
	}
	double fence_len = 0.0;
	for (size_t i = 0; i < ch.size() - 1; ++i)
		fence_len += dist(ch[i], ch[i + 1]);
	fence_len += dist(ch[ch.size() - 1], ch[0]);
	cout << fixed << setprecision(2) << fence_len << endl;
	for (size_t i = 0; i < ch.size() - 1; ++i)
		cout << ch[i].n << " ";
	cout << ch[ch.size() - 1].n << endl;
	cout << endl;
}

int main(int argc, const char *argv[])
{
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		int n;
		vector<Point> points;
		cin >> n;
		for (int j = 0; j < n; ++j) {
			Point p;
			p.n = j + 1;
			cin >> p.x >> p.y;
			points.push_back(p);
		}
		graham_scan(points);
	}
	return 0;
}