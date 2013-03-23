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

const int MAXN = 111111;

struct edge {
	edge *next;
	int to;
	edge(edge *next, int to) : next(next), to(to) {}
};

edge* first_edge[MAXN];
int n, m, l[MAXN], r[MAXN], c[MAXN], u, v, tot, s[MAXN], t[MAXN * 4], len[MAXN * 4];
vector<int> task[MAXN];
bool visited[MAXN];

int build(int x) {
	visited[x] = true;
	l[x] = ++tot;
	s[x] = 1;
	for (edge* it = first_edge[x]; it != NULL; it = it->next) {
		int to = it->to;
		if (!visited[to])
			s[x] += build(to);
	}
	r[x] = tot;
	return s[x];
}

inline void update(int p, int l, int r) {
	len[p] = t[p] > 0 ? r - l + 1 : (l == r ? 0 : len[p * 2] + len[p * 2 + 1]);
}

void cover(int p, int l, int r, int u, int v, bool c) {
	if (u <= l && r <= v) {
		t[p] += c ? 1 : -1;
		update(p, l, r);
		return;
	}
	int mid = (l + r) >> 1;
	if (u <= mid && l <= v)
		cover(p * 2, l, mid, u, v, c);
	if (u <= r && mid < v)
		cover(p * 2 + 1, mid + 1, r, u, v, c);
	update(p, l, r);
}

inline void add_edge(int u, int v) {
	first_edge[u] = new edge(first_edge[u], v);
}

void dfs(int x) {
	for (int i = 0; i < (int)task[x].size(); ++i) {
		int j = task[x][i];
		cover(1, 1, n, l[j], r[j], true);
	}
	if (task[x].size() > 0)
		cover(1, 1, n, l[x], r[x], true);
	visited[x] = true;
	c[x] = len[1];
	if (c[x] > 0)
		--c[x];
	for (edge* it = first_edge[x]; it != NULL; it = it->next) {
		int to = it->to;
		if (!visited[to])
			dfs(to);
	}
	for (int i = 0; i < (int)task[x].size(); ++i) {
		int j = task[x][i];
		cover(1, 1, n, l[j], r[j], false);
	}
	if (task[x].size() > 0)
		cover(1, 1, n, l[x], r[x], false);
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	for (int i = 0; i < m; ++i) {
		scanf("%d %d", &u, &v);
		task[u].push_back(v);
		task[v].push_back(u);
	}
	build(1);
	for (int i = 1; i <= n; ++i)
		visited[i] = false;

	dfs(1);
	for (int i = 1; i <= n; ++i)
		if (i == n)
			printf("%d\n", c[i]);
		else
			printf("%d ", c[i]);
}

