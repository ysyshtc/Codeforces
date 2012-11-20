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

typedef pair<int, int> PII;

const int MAXN = 211111;
const int MAXM = 411111;

bool arr[MAXN], turn[MAXN];
int n, m, u, v, tot, head[MAXN], ans[MAXN], ft[MAXN], deg[MAXN];
vector<PII> ask[MAXN];

struct edge {
	int to, next, index;
	edge(int _t = 0, int _n = 0, int _i = 0) : to(_t), next(_n), index(_i) {}
} g[MAXM];

struct node {
	int u, v, lca;
	node(int _u = 0, int _v = 0) : u(_u), v(_v) {}
} query[MAXN];

int find(int x) { return ft[x] == 0 ? x : ft[x] = find(ft[x]); }

void merge(int u, int v) {
	int p = find(u), q = find(v);
	if (p != q)
		ft[p] = q;
}

void add_edge(int u, int v, int ind) {
	g[++tot] = edge(v, head[u], ind);
	head[u] = tot;
}

void dfs(int x) {
	arr[x] = true;
	for (int i = 0; i < int(ask[x].size()); ++i)
		if (turn[ask[x][i].Y])
			query[ask[x][i].Y].lca = find(ask[x][i].X);
		else
			turn[ask[x][i].Y] = true;

	for (int i = head[x], k; i; i = g[i].next)
		if (!arr[k = g[i].to]) {
			dfs(k);
			merge(k, x);
		}
}

void calc(int x, int y) {
	arr[x] = true;
	int res = deg[x];

	for (int i = head[x], k; i; i = g[i].next)
		if (!arr[k = g[i].to]) {
			calc(k, g[i].index);
			res += ans[g[i].index];
		}
	if (y != -1)
		ans[y] = res;
}

int main(int argc, char* argv[]) {
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		scanf("%d%d", &u, &v);
		add_edge(u, v, i);
		add_edge(v, u, i);
	}
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &u, &v);
		ask[u].push_back(PII(v, i));
		ask[v].push_back(PII(u, i));
		query[i] = node(u, v);
	}
	dfs(1);
	for (int i = 0; i < m; ++i) {
		if (query[i].u != query[i].lca) {
			++deg[query[i].u];
			--deg[query[i].lca];
		}
		if (query[i].v != query[i].lca) {
			++deg[query[i].v];
			--deg[query[i].lca];
		}
	}
	for (int i = 1; i <= n; ++i) arr[i] = false;
	calc(1, -1);
	for (int i = 1; i < n - 1; ++i)
		printf("%d ", ans[i]);
	printf("%d\n", ans[n - 1]);
}
