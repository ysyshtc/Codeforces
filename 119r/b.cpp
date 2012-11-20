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

const int MAXN = 61;
const int INF = 0x3fffffff;

int n, m, r, u, v, c, a[MAXN][MAXN], g[MAXN][MAXN][MAXN];

int main(int argc, char* argv[]) {
	scanf("%d%d%d", &n, &m, &r);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			g[1][i][j] = INF;
	for (int t = 0; t < m; ++t) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				scanf("%d", a[i] + j);
		for (int k = 1; k <= n; ++k)
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				g[1][i][j] = min(g[1][i][j], a[i][j]);
	}
	for (int k = 2; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) {
				g[k][i][j] = INF;
				for (int l = 1; l <= n; ++l)
					g[k][i][j] = min(g[k][i][j], g[k - 1][i][l] + g[1][l][j]);
			}
	for (int i = 0; i < r; ++i) {
		scanf("%d%d%d", &u, &v, &c);
		printf("%d\n", g[min(c + 1, n)][u][v]);
	}
}
