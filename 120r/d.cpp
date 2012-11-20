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

int n, k, p;
long long l, r, ans, tmp;

int pow(int x, long long y, int p) {
	long long res = 1;
	for (long long t = x; y; y >>= 1) {
		if (y & 1)
			res = res * t % p;
		t = t * t % p;
	}
	return res;
}

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	for (cin >> n; n--; ) {
		cin >> k >> l >> r >> p;
		tmp = (pow(k, pow(2, l, p - 1), p) + p - 1) % p;
		if (tmp == 0)
			ans = pow(2, r - l + 1, p);
		else
			ans = (long long)(pow(k, pow(2, r + 1, p - 1), p) + p - 1) * pow(tmp, p - 2, p) % p;
		if (k % p == 0)
			ans = 1;
		if (k & 1)
			ans = ans * pow(pow(2, p - 2, p), r - l, p) % p;
		if (p == 2)
			cout << (k % 2 ^ 1) << endl;
		else
			cout << ans << endl;
	}
}
