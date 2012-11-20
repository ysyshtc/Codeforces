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

int n, ans, f[26], cnt[MAXN], a[MAXN], b[MAXN];
char s[20];

int main(int argc, char* argv[]) {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf(" %s", s);
		cnt[i] = strlen(s);
		a[i] = s[0] - 'a';
		b[i] = s[cnt[i] - 1] - 'a';
	}
	for (int first_char = 0; first_char < 26; ++first_char) {
		for (int i = 0; i < 26; ++i) f[i] = -1;
		for (int i = 0; i < n; ++i) {
			if (f[a[i]] != -1)
				f[b[i]] = max(f[b[i]], f[a[i]] + cnt[i]);
			if (first_char == a[i])
				f[b[i]] = max(f[b[i]], cnt[i]);
		}
		ans = max(ans, f[first_char]);
	}
	printf("%d\n", ans);
}
