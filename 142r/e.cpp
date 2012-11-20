#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

const int MAXN = 1111;

double comb[MAXN][MAXN], dp[MAXN][MAXN];
vector<int> price[MAXN], wish;
int n, m, cnt, tot, spc;

int main() {
	for (int i = 0; i < MAXN; ++i) {
		comb[i][0] = comb[i][i] = 1;
		for (int j = 1; j < i; ++j)
			comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
	}
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; ++i) {
		int q;
		scanf("%d", &q);
		for (int j = 0; j < q; ++j) {
			int x;
			scanf("%d", &x);
			price[i].push_back(x);
			wish.push_back(x);
		}
		sort(price[i].begin(), price[i].end(), greater<int>());
	}
	sort(wish.begin(), wish.end(), greater<int>());
	spc = wish[n - 1];
	for (int i = 0; i < n; ++i)
		if (wish[i] == spc)
			++cnt;

	for (int i = 0; i < (int)wish.size(); ++i)
		if (wish[i] == spc)
			++tot;

	dp[0][0] = 1;
	for (int i = 0; i < m; ++i) {
		int q = (int)price[i].size();
		bool found = false;
		int c = 0;
		for (; c < q && price[i][c] >= spc; ++c)
			if (price[i][c] == spc)
				found = true;

		for (int j = 0; j <= cnt; ++j) {
			dp[i + 1][j] += dp[i][j] / comb[q][c - found];
			if (found) {
				dp[i + 1][j + 1] += dp[i][j] / comb[q][c];
			}
		}
	}
	printf("%.9f\n", dp[m][cnt] / comb[tot][cnt]);
}
