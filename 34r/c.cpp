#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

const int MAXN = 1111;

string s;
vector<pair<int, int> > ans;
bool appear[MAXN];
int x;

int main() {
	getline(cin, s);
	for (int i = 0; i < (int)s.length(); ++i)
		if (s[i] == ',')
			s[i] = ' ';
	istringstream sin(s);
	while (sin >> x) {
		appear[x] = true;
	}
	for (int i = 0; i < MAXN; ++i) {
		if (!appear[i])
			continue;
		int it = i;
		for (; it < MAXN && appear[it]; ++it);
		ans.push_back(make_pair(i, it - 1));
		i = it;
	}
	for (int i = 0; i < (int)ans.size(); ++i) {
		if (ans[i].first == ans[i].second)
			printf("%d", ans[i].first);
		else
			printf("%d-%d", ans[i].first, ans[i].second);
		if (i < (int)ans.size() - 1)
			printf(",");
	}
	puts("");
}
