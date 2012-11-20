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

int n, k, last, it;
char s[MAXN];

inline int find(int p) {
	p = max(0, p);
	for (int i = p; i < n - 1; ++i)
		if (s[i] == '4' && s[i + 1] == '7') {
			if (i & 1)
				s[i] = '7';
			else
				s[i + 1] = '4';
			return i;
		}
	return -1;
}

int main(int argc, char* argv[]) {
	scanf("%d%d", &n, &k);
	scanf("%s", s);
	last = 0;
	for (int i = 0; i < k; ++i) {
		it = find(last - 1);
		if (it == -1)
			break;
		if (it == last - 1)
			k -= (k - i - 1) / 2 * 2;
		last = it;
	}
	puts(s);
}
