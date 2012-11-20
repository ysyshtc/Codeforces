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

const int MAXN = 111;

int cnt, n, m, u, v, circle_tot, que[MAXN], tot;
bool check[MAXN], ans, a[MAXN][MAXN], circle[MAXN];

bool find_circle(int x, int fa, int root) {
	check[x] = true;
	for (int i = 1; i <= n; ++i)
		if (a[x][i] && i != fa)
			if (i == root || !check[i] && find_circle(i, x, root)) {
				circle[x] = true;
				que[circle_tot++] = x;
				return true;
			}
	return false;
}

void tree_dfs(int x, int fa) {
	++tot;
	check[x] = true;
	for (int i = 1; i <= n; ++i)
		if (i != fa && a[x][i])
			if (!circle[x] && (circle[i] || check[i]))
				ans = false;
			else if (!circle[i] && !check[i])
				tree_dfs(i, x);
}

int main(int argc, char* argv[])
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &u, &v);
		a[u][v] = a[v][u] = true;
	}
	for (int i = 1; i <= n; ++i) {
		memset(check, false, sizeof check);
		if (find_circle(i, -1, i)) break;
	}
	ans = circle_tot > 2;
	for (int i = 0; i < circle_tot; ++i) {
		cnt = 0;
		for (int j = 0; j < circle_tot; ++j)
			if (a[que[i]][que[j]]) ++cnt;
		if (cnt > 2) ans = false;
	}
	if (ans)
		for (int i = 1; i <= n; ++i)
			if (circle[i]) {
				memset(check, false, sizeof check);
				tree_dfs(i, -1);
			}
	if (tot < n) ans = false;
	if (ans)
		printf("FHTAGN!\n");
	else
		printf("NO\n");
}
