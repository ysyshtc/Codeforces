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

const int MAXN = 2111;

int n, ans, u;
bool root[MAXN];
vector<int> edge[MAXN];

int dfs(int x) {
	int res = 0;
	for (int i = 0; i < edge[x].size(); ++i)
		res = max(res, dfs(edge[x][i]));
	return res + 1;
}

int main(int argc, char* argv[]) {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &u);
		if (u != -1)
			edge[u].push_back(i);
		else
			root[i] = true;
	}
	ans = 0;
	for (int i = 1; i <= n; ++i)
		if (root[i])
			ans = max(ans, dfs(i));
	printf("%d\n", ans);
}
