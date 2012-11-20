#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <sstream>

using namespace std;

typedef long long ll;
typedef pair<ll, int> PLI;

const int MAXN = 111111;
const int INF = 0x3fffffff;

int n, g, r, t[MAXN], q, lim[MAXN], a[MAXN];
ll s[MAXN], f[MAXN], ans[MAXN];
set<PLI> prt;
set<PLI>::iterator it;

inline void my_insert(ll x, int index) {
	prt.insert(PLI(x % (g + r), index));
	prt.insert(PLI(x % (g + r) + g + r, index));
}

inline void my_del(ll x, int index) {
	prt.erase(prt.find(PLI(x, index)));
	prt.erase(prt.find(PLI((x + g + r) % (g + r + g + r), index)));
}

inline ll up(ll x) {
	return (x / (g + r) + 1) * (g + r);
}

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	scanf("%d%d%d", &n, &g, &r);
	for (int i = 0; i <= n; ++i)
		scanf("%d", a + i);
	for (int i = n - 1; i >= 0; --i) {
		s[i] = s[i + 1] + a[i];
		lim[i] = -1;
	}
	for (int i = 1; i <= n; ++i) {
		my_insert(s[i - 1], i - 1);
		int p = (s[i] + g - 1) % (g + r);
		it = prt.upper_bound(PLI(p, INF));
		while (it != prt.end() && it->first - p <= r) {
			lim[it->second] = i;
			my_del(it->first, it->second);
			it = prt.upper_bound(PLI(p, INF));
		}
	}
	f[n] = a[n];
	for (int i = n - 1; i >= 0; --i)
		if (lim[i] == -1)
			f[i] = a[n] + s[i];
		else
			f[i] = f[lim[i]] + up(s[i] - s[lim[i]]);
	prt.clear();
	scanf("%d", &q);
	for (int i = 0; i < q; ++i) {
		scanf("%d", t + i);
		my_insert(t[i] + s[0], i);
		ans[i] = -1;
	}
	for (int i = 1; i <= n; ++i) {
		int p = (s[i] + g - 1) % (g + r);
		it = prt.upper_bound(PLI(p, INF));
		while (it != prt.end() && it->first - p <= r) {
			ans[it->second] = f[i] + up(t[it->second] + s[0] - s[i]);
			my_del(it->first, it->second);
			it = prt.upper_bound(PLI(p, INF));
		}
	}
	for (int i = 0; i < q; ++i)
		if (ans[i] == -1)
			cout << s[0] + t[i] + a[n] << endl;
		else
			cout << ans[i] << endl;
}
