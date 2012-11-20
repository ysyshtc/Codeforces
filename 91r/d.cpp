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

const ll MAXD = 100000000ll * 1000000000;
const int MAXN = 111111;
const ll INF  = 1111111111ll * 1111111111;

vector<ll> lucky;
int n, lower, upper, ans;
ll lim, lt[MAXN], rt[MAXN], min_len, sum_lt[MAXN], sum_rt[MAXN];

void generate(ll x) {
	if (x)
		lucky.push_back(x);
	if (x < MAXD) {
		generate(x * 10 + 4);
		generate(x * 10 + 7);
	}
}

inline bool cover(ll l, ll r) {
	if (r - l > min_len)
		return false;
	ll res = 0;
	int p = upper_bound(lt, lt + n, l) - lt;
	if (p != n) {
		if (sum_lt[p] >= INF)
			return false;
		if (INF / (n - p) <= (lt[p] - l))
			return false;
		if (INF - sum_lt[p] <= (n - p) * (lt[p] - l))
			return false;
		res = sum_lt[p] + (n - p) * (lt[p] - l);
	}
	p = lower_bound(rt, rt + n, r) - rt - 1;
	if (p != -1) {
		if (sum_rt[p] >= INF)
			return false;
		if (INF / (p + 1) <= (r - rt[p]))
			return false;
		if (INF - sum_rt[p] <= (p + 1) * (r - rt[p]))
			return false;
		if (INF - sum_rt[p] - res <= (p + 1) * (r - rt[p]))
			return false;
		res += sum_rt[p] + (p + 1) * (r - rt[p]);
	}
	return res <= lim;
}

int main(int argc, char* argv[]) {
	generate(0);
	sort(lucky.begin(), lucky.end());
	ios::sync_with_stdio(false);
	cin >> n >> lim;
	min_len = MAXD * 10;
	for (int i = 0; i < n; ++i) {
		cin >> lt[i] >> rt[i];
		min_len = min(rt[i] - lt[i], min_len);
	}
	sort(lt, lt + n);
	sort(rt, rt + n);
	for (int i = 1; i < n; ++i)
		if (sum_rt[i - 1] >= INF)
			sum_rt[i] = INF;
		else if (INF / i <= (rt[i] - rt[i - 1]))
			sum_rt[i] = INF;
		else if (INF - sum_rt[i - 1] <= i * (rt[i] - rt[i - 1]))
			sum_rt[i] = INF;
		else
			sum_rt[i] = sum_rt[i - 1] + i * (rt[i] - rt[i - 1]);
	for (int i = n - 2; i >= 0; --i)
		if (sum_lt[i + 1] >= INF)
			sum_lt[i] = INF;
		else if (INF / (n - i - 1) <= (lt[i + 1] - lt[i]))
			sum_lt[i] = INF;
		else if (INF - sum_lt[i + 1] <= (n - i - 1) * (lt[i + 1] - lt[i]))
			sum_lt[i] = INF;
		else
			sum_lt[i] = sum_lt[i + 1] + (n - i - 1) * (lt[i + 1] - lt[i]);
	for (int i = 0; i < int(lucky.size()); ++i) {
		int lower = i, upper = int(lucky.size()) - 1;
		while (lower < upper) {
			int mid = (lower + upper + 1) / 2;
			if (cover(lucky[i], lucky[mid]))
				lower = mid;
			else
				upper = mid - 1;
		}
		if (cover(lucky[i], lucky[lower]))
			ans = max(ans, lower - i + 1);
	}
	cout << ans << endl;
}
