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
#define MAX(x, y) x = x > (y) ? x : (y)
#define MIN(x, y) x = x > (y) ? (y) : x
#define LOW(x) ((x) & -(x))
#define SQR(x) ((x) * (x))
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define rFOR(i, b, a) for (int i = (b); i > (a); --i)
#define CLEAR(x) memset(x, 0, sizeof(x))
#define FILL(x, p) memset(x, p, sizeof(x))
#define COPY(x, y) memcpy(x, y, sizeof(x))
#define ALL(x) (x).begin(), (x).end()

using namespace std;

typedef long long ll;
typedef unsigned int ui;
typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<string> VS;

const int INF = 0x3fffffff;
const ll _INF = 0x7ffffffffffffffll;
const double EPS = 1e-9;
const double PI = acos(-1.0);

template<class T, class INT>
inline T pow(T x, INT y)
{
	T res(1);
	for (T tt(x); y; y /= 2)
	{
		if (y & 1) res *= tt;
		tt *= tt;
	}
	return res;
}

template<class T, class INT>
inline T pow(T x, INT y, T p)
{
	T res(1);
	for (T tt(x); y; y /= 2)
	{
		if (y & 1) res = res * tt % p;
		tt = tt * tt % p;
	}
	return res;
}

int toInt(string s)
{
	int x = 0;
	istringstream sin(s);
	sin >> x;
	return x;
}

template<class T>
inline string toString(T x)
{
	ostringstream sout;
	sout << x;
	return sout.str();
}

template<class INT>
inline INT gcd(INT x, INT y)
{
	return y ? gcd(y, x % y) : x;
}

template<class INT>
inline int calc_bits(INT x)
{
	return x ? (x & 1) + calc_bits(x >> 1) : 0;
}

const int MAXN = 100000 + 10;
const int MAXD = 2000000;

int n, u, v, sg[MAXN], f[MAXN], tr[MAXD], cnt, cur, tot, ans;
bool nim[MAXD];
PII que[MAXD];
VPII a[MAXN];

int main(int argc, char* argv[])
{
	cin >> n;
	FOR(b, 1, n)
		for (int a = 1; (ll(a) + a + b) * (b + 1) <= 2 * n; ++a) que[tot++] = PII(a, b);
	REP(i, tot)
	{
		u = que[i].X, v = que[i].Y;
		a[(u + u + v) * (v + 1) / 2].push_back(que[i]);
	}
	FOR(i, 3, n + 1)
	{
		cnt = 0;
		REP(j, a[i].size())
		{
			u = a[i][j].X, v = u + a[i][j].Y;
			cur = f[u - 1] ^ f[v];
			nim[tr[cnt++] = cur] = true;
		}
		REP(j, MAXD)
			if (!nim[j])
			{
				sg[i] = j;
				break;
			}
		f[i] = f[i - 1] ^ sg[i];
		REP(j, cnt) nim[tr[j]] = false;
	}
	if (!sg[n]) cout << -1 << endl;
	else
	{
		ans = INF;
		REP(i, a[n].size())
		{
			u = a[n][i].X, v = u + a[n][i].Y;
			if ((f[v] ^ f[u - 1]) == 0) MIN(ans, v - u + 1);
		}
		cout << ans << endl;
	}
}
