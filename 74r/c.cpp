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

const int MAXN = 5000 + 10;

int n, m, cnt, ansx, ansy, x, y, tmp, t;
short u[MAXN], d[MAXN], l[MAXN], r[MAXN];
short _u[MAXN], _d[MAXN], _l[MAXN], _r[MAXN];
string a[MAXN];

inline int calc(const int &x, const int &y)
{
	return x * m + y;
}

inline void del(const int &x, const int &y)
{
	t = calc(x, y);
	if (u[t] > -1) d[calc(u[t], y)] = d[t];
	if (d[t] < n) u[calc(d[t], y)] = u[t];
	if (l[t] > -1) r[calc(x, l[t])] = r[t];
	if (r[t] < m) l[calc(x, r[t])] = l[t];
}

int main(int argc, char* argv[])
{
	cin >> n >> m;
	REP(i, n) cin >> a[i];
	REP(i, n)
		REP(j, m)
		{
			t = calc(i, j);
			l[t] = j - 1;
			r[t] = j + 1;
			u[t] = i - 1;
			d[t] = i + 1;
		}
	REP(i, n)
		REP(j, m)
			if (a[i][j] == '.') del(i, j);
	COPY(_u, u);
	COPY(_d, d);
	COPY(_l, l);
	COPY(_r, r);
	REP(i, n)
		REP(j, m)
			if (a[i][j] != '.')
			{
				COPY(u, _u);
				COPY(d, _d);
				COPY(l, _l);
				COPY(r, _r);
				for (x = i, y = j, cnt = 0; -1 < x && x < n && -1 < y && y < m; ++cnt)
				{
					t = calc(x, y);
					if (a[x][y] == 'U') tmp = u[t], del(x, y), x = tmp;
					else if (a[x][y] == 'D') tmp = d[t], del(x, y), x = tmp;
					else if (a[x][y] == 'L') tmp = l[t], del(x, y), y = tmp;
					else if (a[x][y] == 'R') tmp = r[t], del(x, y), y = tmp;
				}
				if (cnt > ansx) ansx = cnt, ansy = 1;
				else if (cnt == ansx) ++ansy;
			}
	cout << ansx << " " << ansy << endl;
}
