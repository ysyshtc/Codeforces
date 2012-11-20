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

const int MAXN = 511111;
const int MD = 1000003;

int n, m, ans, cnt;
vector<int> a[MAXN];
char c;

inline int check_ver(int x) {
	return x == 1 || x == 4 ? 0 : 1;
}

inline int check_hor(int x) {
	return x == 1 || x == 2 ? 0 : 1;
}

int main(int argc, char* argv[]) {
	scanf("%d%d ", &n, &m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			scanf("%c", &c);
			a[i].push_back(c == '.' ? 0 : c - '0');
		}
		scanf(" ");
	}
	ans = 1;
	for (int i = 0; i < n; ++i) {
		cnt = 2;
		for (int t = 0; t < 2; ++t)
			for (int j = 0; j < m; ++j)
				if (a[i][j] != 0 && check_hor(a[i][j]) != ((j & 1) ^ t)) {
					--cnt;
					break;
				}
		ans = ans * cnt % MD;
	}
	for (int j = 0; j < m; ++j) {
		cnt = 2;
		for (int t = 0; t < 2; ++t)
			for (int i = 0; i < n; ++i)
				if (a[i][j] != 0 && check_ver(a[i][j]) != ((i & 1) ^ t)) {
					--cnt;
					break;
				}
		ans = ans * cnt % MD;
	}
	printf("%d\n", ans);
}
