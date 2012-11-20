#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

const int MAXN = 1111;
const int INF = 0x3fffffff;

int n, a[MAXN], pos, ans;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", a + i);
	}
	ans = INF;
	a[n] = a[0];
	for (int i = 0; i < n; ++i)
		if (abs(a[i] - a[i + 1]) < ans) {
			ans = abs(a[i] - a[i + 1]);
			pos = i;
		}
	printf("%d %d\n", pos + 1, (pos + 1) % n + 1);
}
