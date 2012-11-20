#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <climits>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <utility>
#include <numeric>
#include <memory>
#include <stack>
#include <deque>
#include <queue>
#include <list>
#include <functional>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <bitset>

#define X first
#define Y second
#define LOW(x) ((x) & -(x))
#define SQR(x) ((x) * (x))
#define ALL(x) (x).begin(), (x).end()

using namespace std;

const long long INF = 0x3fffffffll << 30;
const int MAXN = 111111;

int n, root, tot, a[MAXN];
long long lower, upper, mid, k;

struct node {
	int lt, rt, ft, type, size;
	long long val;
	node(int _l = 0, int _r = 0, int _f = 0, int _t = 0, int _s = 0, long long _v = 0) : lt(_l), rt(_r), ft(_f), type(_t), size(_s), val(_v) {}
	inline int &operator[] (const int &p) { return p ? rt : lt; }
} h[MAXN];

void updata(int p) { h[p].size = h[h[p][0]].size + h[h[p][1]].size + 1; }

void fix(int p, int q, int t) {
	h[p].type = t;
	if (t != 2)
		h[q][t] = p;
	if (p != 0)
		h[p].ft = q;
}

void rotate(int p) {
	int ft = h[p].ft, t = h[p].type;
	fix(p, h[ft].ft, h[ft].type);
	fix(h[p][t ^ 1], ft, t);
	fix(ft, p, t ^ 1);
	updata(ft);
}

void splay(int p) {
	while (h[p].type != 2) {
		int ft = h[p].ft;
		if (h[ft].type == 2)
			rotate(p);
		else if (h[ft].type != h[p].type)
			rotate(p), rotate(p);
		else
			rotate(ft), rotate(p);
	}
	root = p;
	updata(root);
}

void insert(long long x) {
	int p = root, lt = 0;
	while (p != 0) {
		lt = p;
		p = h[p][x >= h[p].val];
	}
	h[++tot] = node(0, 0, lt, lt ? x >= h[lt].val : 2, 1, x);
	splay(tot);
}

long long lower_bound(long long x) {
	int p = root, lt = -1;
	long long res = 0;
	while (p != 0) {
		lt = p;
		if (x >= h[p].val)
			res += h[h[p][0]].size + 1;
		p = h[p][x >= h[p].val];
	}
	splay(lt);
	return res;
}

inline long long calc(long long x) {
	long long res = 0, sum = 0;
	root = tot = 0;
	insert(0);
	for (int i = 0; i < n; ++i) {
		sum += a[i];
		res += lower_bound(sum - x);
		insert(sum);
	}
	return res;
}

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (lower = -INF, upper = INF; lower < upper; ) {
		mid = (lower + upper + 1) / 2;
		if (calc(mid) >= k)
			lower = mid;
		else
			upper = mid - 1;
	}
	cout << lower << endl;
}
