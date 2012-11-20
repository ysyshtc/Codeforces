#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

const int MAXN = 111;

int n, m, ans, a[MAXN];

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	for (int i = 0; i < m; ++i)
		if (a[i] < 0)
			ans -= a[i];
	printf("%d\n", ans);
}
