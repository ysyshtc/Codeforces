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

const int MAXN = 111111;

int a[MAXN], b[MAXN], n, tot;
bool fail;

int main(int argc, char* argv[]) {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	for (int i = 0; i < n; ++i)
		if (i > 0 && a[i] != a[i - 1]) {
			b[++tot] = 1;
			if (a[i] > a[i - 1] + 1)
				fail = true;
		}
		else
			++b[tot];
	for (int i = 1; i < tot; ++i)
		if (b[i] < 2)
			fail = true;
	for (int i = 0; i < tot; ++i) {
		if (b[i + 1] < b[i]) {
			fail = true;
			break;
		}
		b[i + 1] -= b[i];
	}
	if (fail || b[tot] != 0)
		puts("NO");
	else
		puts("YES");
}
