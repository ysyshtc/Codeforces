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

const int MAXN = 1111;

struct state {
	int x, y;
	double p;
	state(int x = 0, int y = 0, double p = 0) : x(x), y(y), p(p) {}
};
int n, m, a[MAXN], u[MAXN], v[MAXN];
double dp[MAXN][MAXN];

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for (int i = 0; i < m; ++i)
		scanf("%d %d", u + i, v + i);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j < i; ++j)
			dp[i][j] = 1;
	for (int i = m - 1; i >= 0; --i) {
		vector<state> new_state;
		for (int j = 1; j <= n; ++j)
			if (j != u[i] && j != v[i]) {
				new_state.push_back(state(j, u[i], (dp[j][u[i]] + dp[j][v[i]]) / 2));
				new_state.push_back(state(u[i], j, (dp[u[i]][j] + dp[v[i]][j]) / 2));

				new_state.push_back(state(j, v[i], (dp[j][v[i]] + dp[j][u[i]]) / 2));
				new_state.push_back(state(v[i], j, (dp[v[i]][j] + dp[u[i]][j]) / 2));
			}
		new_state.push_back(state(u[i], v[i], (dp[u[i]][v[i]] + dp[v[i]][u[i]]) / 2));
		new_state.push_back(state(v[i], u[i], (dp[v[i]][u[i]] + dp[u[i]][v[i]]) / 2));

		for (int j = 0; j < (int)new_state.size(); ++j)
			dp[new_state[j].x][new_state[j].y] = new_state[j].p;
	}

	double ans = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j)
			ans += a[i] < a[j] ? dp[i][j] : dp[j][i];
	printf("%.8f\n", ans);
}

