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

int n, x, a[MAXN], b[MAXN], ans, m;

int main(int argc, char* argv[]) {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", a + i);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &x);
		b[x] = i;
	}
	for (int i = 0; i < n; ++i)
		a[i] = b[a[i]];
	int m = -1;
	for (int i = 0; i < n; ++i) {
		if (m > a[i]) {
			ans = n - i;
			break;
		}
		m = max(m, a[i]);
	}
	printf("%d\n", ans);
}
