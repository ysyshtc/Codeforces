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

const int MAXD = 1000000000;

vector<ll> lucky;
int n, k, lim, a[14];
ll ans, t[14];

void generate(ll x) {
	if (x)
		lucky.push_back(x);
	if (x < MAXD) {
		generate(x * 10 + 4);
		generate(x * 10 + 7);
	}
}

inline void permutation(int n, int k) {
	bool select[14];
	memset(select, 0, sizeof select);
	for (int i = 0, p; i < n; ++i) {
		for (p = 1; ; ) {
			for (; p <= n && select[p]; ++p);
			if (k <= t[n - i - 1]) {
				a[i] = p;
				select[p] = true;
				break;
			}
			else {
				k -= t[n - i - 1];
				++p;
			}
		}
	}
}

inline bool find(int x) {
	for (int i = 0; i < int(lucky.size()); ++i)
		if (lucky[i] == x)
			return true;
	return false;
}

int main(int argc, char* argv[]) {
	t[0] = 1;
	for (int i = 1; i < 14; ++i)
		t[i] = t[i - 1] * i;
	cin >> n >> k;
	if (n < 13 && k > t[n]) {
		cout << -1 << endl;
		return 0;
	}
	lim = n > 13 ? n - 13 : 0;
	generate(0);
	sort(lucky.begin(), lucky.end());
	for (int i = 0; i < int(lucky.size()); ++i)
		if (lucky[i] <= lim)
			++ans;
	permutation(min(13, n), k);
	for (int i = 0; i < min(n, 13); ++i)
		if (find(a[i] + lim) && find(i + lim + 1))
			++ans;
	cout << ans << endl;
}
