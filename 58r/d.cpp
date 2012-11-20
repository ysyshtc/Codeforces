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

const int MAXN = 100 + 5;
const int MAXM = 2000 + 10;

int n, m, a[MAXM], p = INF;
bool g[MAXN][MAXN], vis[MAXN];
VI prt;

inline void dfs(int x)
{
	FOR(i, 1, n + 1)
		if (g[x][i])
		{
			g[x][i] = g[i][x] = false;
			dfs(i);
		}
	prt.push_back(x);
}

void _dfs(int x)
{
	vis[x] = true;
	FOR(i, 1, n + 1)
		if (g[x][i] && !vis[i]) _dfs(i);
}

inline bool check(int x, int u, int v)
{
	g[u][v] = g[v][u] = false;
	CLEAR(vis);
	_dfs(a[0]);
	bool res = true;
	FOR(i, x + 1, m)
		if (!vis[a[i]]) res = false;
	g[u][v] = g[v][u] = true;
	return res;
}

int main(int argc, char* argv[])
{
	cin >> n >> m;
	REP(i, m + 1) cin >> a[i];
	rFOR(i, m - 1, -1)
	{
		g[a[i]][a[i + 1]] = g[a[i + 1]][a[i]] = true;
		FOR(j, a[i + 1] + 1, n + 1)
			if (g[a[i]][j] && check(i, a[i], j))
			{
				p = j;
				break;
			}
		if (p != INF)
		{
			g[a[i]][p] = g[p][a[i]] = false;
			REP(j, i + 1) cout << a[j] << " ";
			dfs(p);
			rFOR(j, prt.size() - 1, -1) cout << prt[j] << " ";
			cout << endl;
			return 0;
		}
	}
	cout << "No solution" << endl;
}
