#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

const int MAXN = 51111;

struct edge {
	edge* next;
	int to;
	edge(edge* next, int to) : next(next), to(to) {}
};

edge* head[MAXN];
int n, r1, r2, u, father[MAXN];

void add_edge(int u, int v) {
	head[u] = new edge(head[u], v);
}

int main() {
	scanf("%d %d %d", &n, &r1, &r2);
	for (int i = 1; i <= n; ++i) {
		if (i == r1)
			continue;
		scanf("%d", &u);
		add_edge(u, i);
		add_edge(i, u);
	}
	queue<int> Q;
	for (int i = 1; i <= n; ++i)
		father[i] = 0;
	father[r2] = -1;
	Q.push(r2);
	while (!Q.empty()) {
		int now = Q.front();
		Q.pop();
		for (edge* cur = head[now]; cur != NULL; cur = cur->next) {
			int k = cur->to;
			if (father[k] == 0) {
				father[k] = now;
				Q.push(k);
			}
		}
	}
	vector<int> ans;
	for (int i = 1; i <= n; ++i) {
		if (i != r2)
			ans.push_back(father[i]);
	}
	for (int i = 0; i < (int)ans.size(); ++i)
		if (i < (int)ans.size() - 1)
			printf("%d ", ans[i]);
		else
			printf("%d\n", ans[i]);
}
