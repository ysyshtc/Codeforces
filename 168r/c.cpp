#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>

using namespace std;

const double EPS = 1e-6;
struct Point {
	double x, y;
	Point(double x = 0, double y = 0) : x(x), y(y) {}
};
inline Point operator+ (const Point &a, const Point &b) {
	return Point(a.x + b.x, a.y + b.y);
}
inline Point operator- (const Point &a, const Point &b) {
	return Point(a.x - b.x, a.y - b.y);
}
inline Point operator* (const Point &a, const double &b) {
	return Point(a.x * b, a.y * b);
}
inline Point operator/ (const Point &a, const double &b) {
	return Point(a.x / b, a.y / b);
}
inline double dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}
inline double det(const Point &a, const Point &b) {
	return a.x * b.y - b.x * a.y;
}
inline double norm2(const Point &a) {
	return dot(a, a);
}
inline Point circumcenter(const Point &a, const Point &b, const Point &c) {
	Point p = b - a, q = c - a, s(dot(p, p) / 2, dot(q, q) / 2);
	double d = det(p, q);
	return a + Point(det(s, Point(p.y, q.y)), det(Point(p.x, q.x), s)) / d;
}
inline double dist(const Point &a, const Point &b) {
	return sqrt(dot(a - b, a - b));
}
inline bool check(Point *p, int n, Point o, double r) {
	for (int i = 0; i < n; ++i)
		if (dist(p[i], o) < r - EPS)
			return false;
	return true;
}
inline bool equals(double a, double b) {
	return fabs(a - b) < EPS;
}

const int MAXN = 111;

int main() {
	int n;
	Point p[MAXN];
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		double x, y;
		scanf("%lf %lf", &x, &y);
		p[i] = Point(x, y);
	}
	double ret = -1.0;
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			for (int k = j + 1; k < n; ++k) {
				double a = norm2(p[i] - p[j]), b = norm2(p[j] - p[k]), c = norm2(p[k] - p[i]);
				if (a + b > c + EPS && b + c > a + EPS && c + a > b + EPS) {		//acute
					Point o = circumcenter(p[i], p[j], p[k]);
					double r = dist(p[i], o);
					if (check(p, n, o, r))
						ret = max(r, ret);
				}
			}
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j) {
			Point o = (p[i] + p[j]) / 2;
			double r = dist(p[i], o);
			if (check(p, n, o, r)) {
				int cnt = 0;
				for (int k = 0; k < n; ++k)
					if (equals(dist(p[k], o), r) && fabs(dot(p[k] - o, p[i] - o)) < EPS)
						++cnt;
				if (cnt == 2)
					ret = max(r, ret);
			}
		}

	if (ret < EPS)
		puts("-1");
	else
		printf("%.6f\n", ret);
}

