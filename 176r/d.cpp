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

struct Segment {
	int l, r, t;
	bool type;
	Segment(int l = 0, int r = 0, int t = 0) : l(l), r(r), t(t) {}
	void out() {
		printf("%d %d %d\n", l, r, t);
	}
};

struct Event {
	int key, val;
	bool type;
	Event(int key = 0, int val = 0, bool type = false) : key(key), val(val), type(type) {}
};

inline bool cmp_time(const Segment &a, const Segment &b) {
	return a.t < b.t;
}

inline bool cmp(const Event &a, const Event &b) {
	return a.key > b.key;
}

const int MAXN = 2 * (int)1e5;
const int MAXM = 2 * (int)1e5;
const int INF = 0x3fffffff;

Segment a[MAXM];
Event b[MAXM * 2];
int nx[MAXN], tv[MAXN], q[MAXN];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<int> key;
	for (int i = 0; i < m; ++i) {
		int u, v, t;
		scanf("%d %d %d", &u, &v, &t);
		a[i] = Segment(u, v, t);
		key.push_back(u);
		key.push_back(v);
	}
	for (int i = 0; i < n; ++i)
		scanf("%d", q + i);

	sort(key.begin(), key.end());
	key.erase(unique(key.begin(), key.end()), key.end());
	for (int i = 0; i < m; ++i) {
		a[i].l = lower_bound(key.begin(), key.end(), a[i].l) - key.begin();
		a[i].r = lower_bound(key.begin(), key.end(), a[i].r) - key.begin();
	}
	sort(a, a + m, cmp_time);
	int L = key.size();
	for (int i = 0; i < L; ++i) {
		nx[i] = i + 1;
		tv[i] = -1;
	}
	for (int i = 0; i < m; ++i) {
		for (int j = a[i].l; j < a[i].r; ) {
			if (tv[j] == -1)
				tv[j] = a[i].t;
			int last = j;
			j = nx[j];
			nx[last] = max(nx[last], a[i].r);
		}
	}
	int tot = 0;
	for (int i = 0; i < L - 1; ++i)
		if (tv[i] != -1) {
			b[tot++] = Event(key[i] - tv[i], key[i + 1] - tv[i], false);
			b[tot++] = Event(key[i + 1] - tv[i], key[i] - tv[i], true);
		}
	sort(b, b + tot, cmp);
	int count = 0, ret = 0, it = 0, last = INF;
	for (int i = 0; i < n; ++i) {
		int nc = 0;
		for (; it < tot && -q[i] <= b[it].key; ++it) {
			if (!b[it].type) {
				if (b[it].val < last)
					ret += b[it].val - b[it].key;
				else {
					--count;
					ret += last - b[it].key;
				}
			}
			else {
				if (b[it].val < -q[i]) {
					++nc;
					ret += b[it].key + q[i];
				}
			}
		}
		ret += count * (q[i] + last);
		last = -q[i];
		count += nc;
		printf("%d\n", ret);
	}
}

