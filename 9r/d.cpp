#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

typedef long long ll;

const int MAXN = 37;

ll dp[MAXN][MAXN][MAXN];
int n, h;

int main() {
	scanf("%d %d", &n, &h);
	for (int i = 1; i <= n + 1; ++i)
		dp[i][i - 1][0] = 1;
	for (int i = 1; i <= n; ++i)
		dp[i][i][1] = 1;

	for (int j = 2; j <= n; ++j)
		for (int i = j - 1; i > 0; --i)
			for (int k = 1; k <= j - i + 1; ++k)
				for (int l = i; l <= j; ++l) {
					for (int t = 0; t < k; ++t)
						dp[i][j][k] += dp[i][l - 1][k - 1] * dp[l + 1][j][t];
					for (int t = 0; t < k - 1; ++t)
						dp[i][j][k] += dp[i][l - 1][t] * dp[l + 1][j][k - 1];
				}
	ll ret = 0;
	for (int i = h; i <= n; ++i)
		ret += dp[1][n][i];
	cout << ret << endl;
}
