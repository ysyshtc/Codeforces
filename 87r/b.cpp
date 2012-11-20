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

const int MAXN = 160;

int n, m, lt[MAXN], rt[MAXN], ans, now, nx, c;
char s[MAXN];

int main(int argc, char* argv[]) {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		lt[i] = -1, rt[i] = -1;
		scanf("%s", s);
		for (int j = 0; j < m; ++j)
			if (s[j] == 'W') {
				rt[i] = j;
				if (lt[i] == -1) lt[i] = j;
			}
	}
	if (lt[0] == -1)
		lt[0] = 0, rt[0] = 0;
	while (now < n) {
		for (nx = now + 1; nx < n && lt[nx] == -1; ++nx);
		if (nx == n) {
			ans += max(abs(c - rt[now]), abs(lt[now] - c));
			break;
		}
		if (nx - now & 1)
			if ((now & 1) == 0) {
				ans += max(rt[nx], rt[now]) - c;
				c = max(rt[nx], rt[now]);
			}
			else {
				ans += c - min(lt[nx], lt[now]);
				c = min(lt[nx], lt[now]);
			}
		else
			if ((now & 1) == 0) {
				ans += rt[now] - c + abs(lt[nx] - rt[now]);
				c = lt[nx];
			}
			else {
				ans += c - lt[now] + abs(rt[nx] - lt[now]);
				c = rt[nx];
			}
		ans += nx - now;
		now = nx;
	}
	printf("%d\n", ans);
}
