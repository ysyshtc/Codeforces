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

ll l, r, ans;
int p;
vector<ll> lucky;

void generate(ll x) {
	if (x)
		lucky.push_back(x);
	if (x < MAXD) {
		generate(x * 10 + 4);
		generate(x * 10 + 7);
	}
}

int main(int argc, char* argv[]) {
	cin >> l >> r;
	generate(0);
	sort(lucky.begin(), lucky.end());
	p = lower_bound(lucky.begin(), lucky.end(), l) - lucky.begin();
	for (--l; lucky[p] < r; ++p) {
		ans += ll(lucky[p] - l) * lucky[p];
		l = lucky[p];
	}
	ans += (r - l) * lucky[p];
	cout << ans << endl;
}
