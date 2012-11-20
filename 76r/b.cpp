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

int n, w, m, now;
double rem, cur, cnt;

int main(int argc, char* argv[])
{
	cin >> n >> w >> m;
	if (n >= m)
	{
		cout << "YES" << endl;
		now = -1, rem = 0;
		REP(i, m)
		{
			cnt = double(n) * w / m;
			while (abs(cnt) > EPS)
			{
				if (abs(rem) < EPS)
					++now, rem = w;
				cur = min(rem, cnt);
				cout << now + 1 << " " << setprecision(7) << fixed << cur << " ";
				cnt -= cur, rem -= cur;
			}
			cout << endl;
		}
	}
	else if (n * 2 < m)
		cout << "NO" << endl;
	else if (n % (m - n) == 0)
	{
		cout << "YES" << endl;
		cnt = double(n) * w / m;
		REP(i, n)
			cout << i + 1 << " " << setprecision(7) << fixed << cnt << endl;
		now = 0;
		REP(i, m - n)
		{
			REP(j, n / (m - n))
				cout << ++now << " " << setprecision(7) << fixed << w - cnt << " ";
			cout << endl;
		}
	}
	else
		cout << "NO" << endl;
}
