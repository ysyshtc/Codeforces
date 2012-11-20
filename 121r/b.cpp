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

int n, k, a[MAXN], t[MAXN];
long long m, sum, tmp;
bool buy[MAXN];

struct node {
	int val, index;
	node(int _v = 0, int _i = 0) : val(_v), index(_i) {}
} b[MAXN];

inline bool operator< (const node &a, const node &b) {
	if (a.val != b.val)
		return a.val > b.val;
	return a.index > b.index;
}

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin >> n >> k >> m;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		b[i] = node(a[i], i);
	}
	sort(b, b + n - 1);
	for (int i = 0; i < n - 1; ++i)
		t[b[i].index] = i;
	for (int i = 0; i < k - 1; ++i)
		sum += b[i].val;
	for (int i = 0; i < n; ++i) {
		tmp = t[i] < k - 1 ? sum - a[i] + b[k - 1].val : sum;
		if (i == n - 1 || tmp + a[i] > m) {
			cout << i + 1 << endl;
			break;
		}
	}
}
