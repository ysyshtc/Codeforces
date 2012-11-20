#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

const double EPS = 1e-8;
const int MAXN = 11;

struct object {
	double pos, speed, mass;
	int index;
	object(double pos = 0, double speed = 0, double mass = 0, double index = 0) : pos(pos), speed(speed), mass(mass), index(index) {}
	object move(double time) {
		return object(pos + time * speed, speed, mass, index);
	}
};
inline bool operator< (const object &a, const object &b) {
	return a.pos + EPS < b.pos;
}

inline bool collide(object a, object b) {
	return fabs(a.pos - b.pos) < EPS;
}

inline void swap_movement(object &a, object &b) {
	double u = a.speed, v = b.speed;
	a.speed = ((a.mass - b.mass) * u + 2 * b.mass * v) / (a.mass + b.mass);
	b.speed = ((b.mass - a.mass) * v + 2 * a.mass * u) / (a.mass + b.mass);
}

inline double solve(object a, object b) {
	if (fabs(a.speed) + fabs(b.speed) < EPS)
		return 1e10;
	if (a.speed * b.speed >= 0) {
		if (a.speed < b.speed)
			return 1e10;
		else
			return (b.pos - a.pos) / (a.speed - b.speed);
	}
	else {
		if (a.speed < 0)
			return 1e10;
		else
			return (b.pos - a.pos) / (a.speed - b.speed);
	}
}

double ans[MAXN];
int n, t, x, v, m;
object a[MAXN];

int main() {
	scanf("%d %d", &n, &t);
	for (int i = 0; i < n; ++i) {
		scanf("%d %d %d", &x, &v, &m);
		a[i] = object(x, v, m, i);
	}
	sort(a, a + n);
	double tt = 0;
	while (tt + EPS < t) {
		double coll = t - tt;
		for (int i = 1; i < n; ++i)
			coll = min(coll, solve(a[i - 1], a[i]));
		for (int i = 0; i < n; ++i)
			a[i] = a[i].move(coll);
		tt += coll;
		for (int i = 0; i < n; ++i)
			if (collide(a[i - 1], a[i]))
				swap_movement(a[i - 1], a[i]);
	}
	for (int i = 0; i < n; ++i)
		ans[a[i].index] = a[i].pos;
	for (int i = 0; i < n; ++i)
		printf("%.6f\n", ans[i]);
}
