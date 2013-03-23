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

const int MAXN = 12;
const int MOD = (int)1e9 + 7;

int n, m, len, dp[MAXN][MAXN], ten[MAXN][MAXN], c[MAXN][MAXN];

int add_mod(int a, int b) {
	if (a + b >= MOD)
		return a + b - MOD;
	return a + b;
}

int mul_mod(int a, int b) {
	return (long long)a * b % MOD;
}

int perm(int n, int m) {
	int ret = 1;
	for (int i = 0; i < m; ++i)
		ret = mul_mod(ret, n - i);
	return ret;
}

int pow_mod(int x, int y) {
	if (y == 0)
		return 1;
	int ret = pow_mod(x, y / 2);
	ret = mul_mod(ret, ret);
	if (y & 1)
		ret = mul_mod(x, ret);
	return ret;
}

int inverse(int n) {
	return pow_mod(n, MOD - 2);
}

int perm(int n) {
	return perm(n, n);
}

int dfs(int n, int limit, int m) {
	if (n == 0) {
		return 1;
	}
	if (limit <= n * m)
		return 0;

	int ret = 0;
	for (int i = 0; i <= n; ++i) {
		if (i * m < limit)
			ret = add_mod(ret, mul_mod(inverse(perm(i)), mul_mod(perm(dp[len][m], i), dfs(n - i, limit - i * m, m + 1))));
	}
	return ret;
}

int main() {
	scanf("%d", &n);

	dp[0][0] = 1;
	ten[0][0] = 1;
	for (int m = n, i = 1; m > 0; m /= 10, ++i) {
		for (int j = 0; j <= i; ++j) {
			ten[i][j] = (ten[i - 1][j] << 3) + (j ? ten[i - 1][j - 1] << 1 : 0);
		}
		int val = m % 10;
		for (int j = 0; j <= i; ++j) {
			for (int k = 0; k < val; ++k)
				if (k == 4 || k == 7) {
					if (j > 0)
						dp[i][j] += ten[i - 1][j - 1];
				}
				else
					dp[i][j] += ten[i - 1][j];
			int cost = val == 4 || val == 7;
			if (j >= cost)
				dp[i][j] += dp[i - 1][j - cost];
		}
		len = i;
	}
	--dp[len][0];

	int ans = 0;
	for (int i = 0; i <= len; ++i)
		ans = add_mod(ans, mul_mod(dp[len][i], dfs(6, i, 0)));
	printf("%d\n", mul_mod(perm(6), ans));
}

