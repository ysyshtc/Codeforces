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
typedef pair<double, double> PDD;

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

const int MAXN = 100 + 10;

int n, cnt;
double stc[MAXN * 3], ans;
PDD a[MAXN][3];

inline double dis(PDD a, PDD b)
{
	return sqrt(SQR(a.X - b.X) + SQR(a.Y - b.Y));
}

inline PDD operator- (PDD a, PDD b)
{
	return PDD(a.X - b.X, a.Y - b.Y);
}

inline double operator* (PDD a, PDD b)
{
	return a.X * b.Y - b.X * a.Y;
}

inline double cross(PDD a, PDD b, PDD c)
{
	return (a - c) * (b - c);
}

inline bool ins(PDD t, int x)
{
	double s1 = abs(cross(a[x][0], a[x][1], t));
	double s2 = abs(cross(a[x][1], a[x][2], t));
	double s3 = abs(cross(a[x][2], a[x][0], t));
	return abs(s1 + s2 + s3 - abs(cross(a[x][0], a[x][1], a[x][2]))) < EPS;
}

int main(int argc, char* argv[])
{
	cin >> n;
	REP(i, n)
		REP(j, 3) cin >> a[i][j].X >> a[i][j].Y;
	REP(i, n)
		REP(j, 3)
		{
			PDD p = a[i][j], q = a[i][(j + 1) % 3];
			double w = dis(p, q);
			cnt = 2;
			stc[0] = 0, stc[1] = 1;
			REP(k, n)
				if (k != i) REP(l, 3)
				{
					PDD s = a[k][l], t = a[k][(l + 1) % 3];
					double s1 = cross(p, s, t), s2 = cross(q, s, t);
					if (s1 < 0 && s2 > 0 || s1 > 0 && s2 < 0)
						stc[cnt++] = s1 / (s1 - s2);
				}
			sort(stc, stc + cnt);
			REP(k, cnt - 1)
			{
				double r = (stc[k] + stc[k + 1]) / 2;
				PDD cen(p.X + (q.X - p.X) * r, p.Y + (q.Y - p.Y) * r);
				bool check = false;
				REP(l, n)
					if (l != i && ins(cen, l)) check = true;
				if (!check) ans += w * (stc[k + 1] - stc[k]);
			}
		}
	cout << setprecision(10) << fixed << ans << endl;
}
