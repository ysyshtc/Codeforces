#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>

using namespace std;

struct Panel {
	int l, r, h, t;
	Panel(int l = 0, int r = 0, int h = 0, int t = 0) : l(l), r(r), h(h), t(t) {}
};
inline bool operator< (const Panel &a, const Panel &b) {
	return a.l < b.l;
}
inline bool cmp(const Panel &a, const Panel &b) {
	return a.h < b.h;
}

const int MAXN = 111111;
const int INF = (int)1e9;
Panel a[MAXN];

int main() {
	int n, t;
	scanf("%d %d", &n, &t);
	for (int i = 0; i < n; ++i) {
		int h, l, r;
		scanf("%d %d %d", &h, &l, &r);
		a[i] = Panel(l, r, h);
	}
	sort(a, a + n, cmp);
	set<Panel> fall;
	fall.insert(Panel(-INF, INF, 2 * INF));
	
	a[n] = Panel(-INF, INF, t);
	for (int i = 0; i <= n; ++i) {
		Panel val = a[i];
		set<Panel>::iterator it = fall.lower_bound(val);
		if (it != fall.begin())
			--it;
		vector<Panel> offer, poll;
		int ret = 0;
		for (; it != fall.end() && it->l < val.r; ++it) {
			if (val.l < it->r) {
				poll.push_back(*it);
				if (it->l < val.l) {
					offer.push_back(Panel(it->l, val.l, it->h, it->t | 2));
				}
				if (it->r > val.r) {
					offer.push_back(Panel(val.r, it->r, it->h, it->t | 1));
				}
				if (!((it->t & 1) && val.l < it->l || (it->t & 2) && it->r < val.r))
					ret = max(ret, min(it->h, min(val.r, it->r) - max(val.l, it->l)));
			}
		}
		for (int i = 0; i < (int)poll.size(); ++i)
			fall.erase(poll[i]);
		for (int i = 0; i < (int)offer.size(); ++i)
			fall.insert(offer[i]);
		fall.insert(Panel(val.l, val.r, ret));
	}

	printf("%d\n", fall.begin()->h);
}

