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

int n, m, l, r, f[MAXN], g[MAXN], s[MAXN], que[MAXN], par[MAXN], u, v, cnt, tot;
ll sum, tt[MAXN], ans;
bool prt[MAXN], check[MAXN];
VI edge[MAXN], tr[MAXN];
struct Node
{
	int x, y, c, p;
} a[MAXN];

inline bool cmp(Node a, Node b)
{
	return a.c < b.c;
}

inline void add(int u, int v, int p)
{
	edge[u].push_back(v);
	tr[u].push_back(p);
}

int find(int x)
{
	return f[x] ? f[x] = find(f[x]) : x;
}

ll dfs(int x, int r, bool t)
{
	check[x] = true;
	ll res = s[x], tmp;
	REP(i, edge[x].size())
	{
		int k = edge[x][i];
		if (k != r)
		{
			tmp = dfs(k, x, t);
			if (t) tt[tr[x][i]] = tmp * (sum - tmp);
			res += tmp;
		}
	}
	return res;
}

int main(int argc, char* argv[])
{
	cin >> n, m = n - 1;
	REP(i, m) cin >> a[i].x >> a[i].y >> a[i].c, a[i].p = i;
	sort(a, a + m, cmp);
	FOR(i, 1, n + 1) g[i] = 1;
	for (int l = 0, r = 0; l < m; l = r)
	{
		for (r = l; r < m && a[r].c == a[l].c; ++r);
		cnt = 0;
		FOR(i, l, r)
		{
			u = find(a[i].x), v = find(a[i].y);
			if (!par[u]) que[par[u] = ++cnt] = u, s[cnt] = g[u];
			if (!par[v]) que[par[v] = ++cnt] = v, s[cnt] = g[v];
			add(par[u], par[v], i);
			add(par[v], par[u], i);
		}
		FOR(i, 1, cnt + 1)
			if (!check[i])
				sum = dfs(i, 0, false), dfs(i, 0, true);
		FOR(i, l, r)
		{
			u = find(a[i].x), v = find(a[i].y);
			f[u] = v, g[v] += g[u];
		}
		FOR(i, 1, cnt + 1)
			par[que[i]] = 0, edge[i].clear(), tr[i].clear(), check[i] = false;
	}
	REP(i, m) MAX(ans, tt[i]);
	REP(i, m)
		if (ans == tt[i]) prt[a[i].p] = true, ++tot;
	cout << ans * 2 << " " << tot << endl;
	REP(i, m)
		if (prt[i]) cout << i + 1 << " ";
	cout << endl;
}
