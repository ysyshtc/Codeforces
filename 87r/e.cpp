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

typedef long long ll;

const int MAXN = 211111;
const int MAXD = 1111111;

struct Node {
	int key, value;
	Node() {}
	Node(int _k, int _v) : key(_k), value(_v) {}
};
vector<Node> triplet[MAXN];
int n, m, u, v, cost, a[MAXN];
ll f[MAXN], h[MAXD], g[MAXD];

inline void fix(int p, ll c) {
	h[p] += c, g[p] += c;
}

void insert(int p, int l, int r, int u, int v, ll c) {
	if (u <= l && r <= v) {
		fix(p, c);
		return;
	}
	int mid = (l + r) / 2;
	if (h[p]) {
		fix(p * 2, h[p]);
		fix(p * 2 + 1, h[p]);
		h[p] = 0;
	}
	if (l <= v && u <= mid) insert(p * 2, l, mid, u, v, c);
	if (mid < v && u <= r) insert(p * 2 + 1, mid + 1, r, u, v, c);
	g[p] = max(g[p * 2], g[p * 2 + 1]);
}

ll get(int p, int l, int r, int u) {
	if (r <= u)
		return g[p];
	int mid = (l + r) / 2;
	if (h[p]) {
		fix(p * 2, h[p]);
		fix(p * 2 + 1, h[p]);
		h[p] = 0;
	}
	if (u <= mid) return get(p * 2, l, mid, u);
	else return max(g[p * 2], get(p * 2 + 1, mid + 1, r, u));
}

int main(int argc, char* argv[]) {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for (int i = 0; i < m; ++i) {
		scanf("%d%d%d", &u, &v, &cost);
		triplet[v].push_back(Node(u, cost));
	}
	for (int i = 1; i <= n; ++i) {
		insert(1, 1, n, 1, i, -a[i]);
		for (int j = 0; j < triplet[i].size(); ++j)
			insert(1, 1, n, 1, triplet[i][j].key, max(0, triplet[i][j].value));
		f[i] = max(f[i - 1], get(1, 1, n, i));
		if (i < n) insert(1, 1, n, i + 1, i + 1, f[i]);
	}
	cout << f[n] << endl;
}
