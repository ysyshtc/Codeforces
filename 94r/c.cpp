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

typedef long long ll;

const int MAXN = 1001;
const int MD = 1000000007;

int n, m, k, c[MAXN][MAXN];

int main(int argc, char* argv[]) {
	c[0][0] = 1;
	for (int i = 1; i < MAXN; ++i) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; ++j)
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MD;
	}
	scanf("%d%d%d", &n, &m, &k);
	if (2 * k > n - 1 || 2 * k > m - 1)
		cout << 0 << endl;
	else
		cout << ll(c[n - 1][2 * k]) * c[m - 1][2 * k] % MD << endl;
}
