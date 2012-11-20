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

const int MAXN = 100 + 10;

int n, p, q, cnt;
string s, t, tt;
struct Node
{
	string name;
	int x, y, att;
	ll w, h;
	VI r;
} tmp;
vector<Node> v;
map<string, int> a;
bool check[MAXN];

inline bool cmp(const Node &a, const Node &b)
{
	return a.name < b.name;
}

void dfs(int x)
{
	check[x] = true;
	int k;
	ll w = 0, h = 0;
	REP(i, v[x].r.size())
	{
		k = v[x].r[i];
		if (!check[k]) dfs(k);
		if (v[x].att == 1) w += v[k].w, MAX(h, v[k].h);
		if (v[x].att == 2) MAX(w, v[k].w), h += v[k].h;
	}
	if (v[x].r.size())
		if (v[x].att == 1)
		{
			v[x].h = h + 2 * v[x].x;
			v[x].w = w + (v[x].r.size() - 1) * v[x].y + 2 * v[x].x;
		}
		else
		{
			v[x].h = h + (v[x].r.size() - 1) * v[x].y + 2 * v[x].x;
			v[x].w = w + 2 * v[x].x;
		}
}

int main(int argc, char* argv[])
{
	scanf("%d ", &n);
	REP(i, n)
	{
		getline(cin, s);
		p = s.find(' ');
		if (p < s.size())
		{
			t = s.substr(0, p);
			if (t == "Widget")
			{
				q = s.find('(');
				tmp.name = s.substr(p + 1, q - p - 1);
				tmp.att = 0;
				tmp.x = tmp.y = 0;
				s.erase(0, q + 1);
				q = s.find(',');
				tmp.w = toInt(s.substr(0, q));
				s.erase(0, q + 1);
				tmp.h = toInt(s.substr(0, s.size() - 1));
				a[tmp.name] = cnt++;
				v.push_back(tmp);
			}
			else if (t == "HBox")
			{
				q = s.size();
				tmp.name = s.substr(p + 1, q - p - 1);
				tmp.x = tmp.y = 0;
				tmp.w = tmp.h = 0;
				tmp.att = 1;
				v.push_back(tmp);
				a[tmp.name] = cnt++;
			}
			else 
			{
				q = s.size();
				tmp.name = s.substr(p + 1, q - p - 1);
				tmp.x = tmp.y = 0;
				tmp.w = tmp.h = 0;
				tmp.att = 2;
				v.push_back(tmp);
				a[tmp.name] = cnt++;
			}
		}
		else
		{
			p = s.find('.');
			t = s.substr(0, p);
			s.erase(0, p + 1);
			if (s.substr(0, 4) == "pack")
			{
				s.erase(0, 5);
				q = a[t];
				tt = s.substr(0, s.size() - 1);
				v[q].r.push_back(a[tt]);
			}
			else if (s.substr(0, 5) == "set_b")
			{
				s.erase(0, 11);
				q = toInt(s.substr(0, s.size() - 1));
				v[a[t]].x = q;
			}
			else
			{
				s.erase(0, 12);
				q = toInt(s.substr(0, s.size() - 1));
				v[a[t]].y = q;
			}
		}
	}
	REP(i, cnt)
		if (!check[i]) dfs(i);
	sort(ALL(v), cmp);
	REP(i, cnt)
		cout << v[i].name << " " << v[i].w << " " << v[i].h << endl;
}
