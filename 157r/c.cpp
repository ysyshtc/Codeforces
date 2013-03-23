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
const int MOD = (int)1e9 + 7;

int n, ans, a[MAXN];
vector<int> factor[MAXN];

int add_mod(int a, int b) {
	return a + b >= MOD ? a + b - MOD : a + b;
}

int mul_mod(int a, int b) {
	return (long long)a * b % MOD;
}

int sub_mod(int a, int b) {
	return a < b ? a + MOD - b : a - b;
}

int pow_mod(int x, int y) {
	if (y == 0)
		return 1;
	int ret = pow_mod(x, y / 2);
	ret = mul_mod(ret, ret);
	if (y & 1)
		ret = mul_mod(ret, x);
	return ret;
}

int main() {
	for (int i = 1; i < MAXN; ++i)
		for (int j = i; j < MAXN; j += i)
			factor[j].push_back(i);

	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	for (int i = 1; i < MAXN; ++i) {
		int last = n, ret = 1;
		for (int j = (int)factor[i].size() - 1; j >= 0; --j) {
			int it = lower_bound(a, a + n, factor[i][j]) - a;
			int tot = last - it;
			if (factor[i][j] == i)
				ret = mul_mod(ret, sub_mod(pow_mod(j + 1, tot), pow_mod(j, tot)));
			else
				ret = mul_mod(ret, pow_mod(j + 1, tot));
			last = it;
		}
		ans = add_mod(ans, ret);
	}
	printf("%d\n", ans);
}

