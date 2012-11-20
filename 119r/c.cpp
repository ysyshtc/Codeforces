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

const int MAXN = 211111;
const int MAXM = 411111;
const int MAXQ = 51111111;
const int INF = 0x3fffffff;

int n, m, k, u, v, b[MAXN], dis[MAXN], que[MAXQ], head[MAXN], next[MAXM], to[MAXM], tot, S, T, ft[MAXN];
bool a[MAXN], arr[MAXN];

int root(int x) { return ft[x] == 0 ? x : ft[x] = root(ft[x]); }

inline void merge(int u, int v) {
	int p = root(u), q = root(v);
	if (p != q)
		ft[p] = q;
}

inline void add_edge(int u, int v) {
	next[++tot] = head[u];
	head[u] = tot;
	to[tot] = v;
	merge(u, v);
}

int main(int argc, char* argv[]) {
	scanf("%d%d%d", &n, &m, &k);

	for (int i = 0; i < k; ++i)
		scanf("%d", b + i);

	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}

	scanf("%d%d", &S, &T);
	if (root(S) != root(T)) {
		puts("-1");
		return 0;
	}

	int lower = 1, upper = n, mid;
	while (lower < upper) {
		mid = (lower + upper) >> 1;
		for (int i = 1; i <= n; ++i) {
			dis[i] = INF;
			arr[i] = false;
		}
		for (int i = 0; i < k; ++i)
			dis[b[i]] = 0;
		a[S] = true;
		que[1] = S;
		for (int fore = 0, rear = 1; fore++ < rear; ) {
			int now = que[fore];
			arr[now] = true;
			for (int i = head[now], k; i; i = next[i]) {
				if (dis[now] == mid)
					break;
				k = to[i];
				if (dis[now] + 1 < dis[k] || !arr[k]) {
					dis[k] = min(dis[k], dis[now] + 1);
					if (!a[k]) {
						a[k] = true;
						que[++rear] = k;
					}
				}
			}
			a[now] = false;
		}
		if (arr[T])
			upper = mid;
		else
			lower = mid + 1;
	}
	printf("%d\n", lower);
}
