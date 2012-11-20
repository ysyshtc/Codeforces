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

long long n, k, x;
int p;

int main(int argc, char* argv[])
{
	cin >> n >> k >> p;
	for (int i = 0; i < p; ++i) {
		cin >> x;
		if (k > n - k) {
			if (x <= 2 * (n - k))
				if (x & 1)
					cout << ".";
				else
					cout << "X";
			else
				cout << "X";
		}
		else {
			if (k == 0)
				cout << ".";
			else if (x == n)
				cout << "X";
			else if (k == 1)
				cout << ".";
			else if (n & 1) {
				if (x <= n - 2 * k + 1)
					cout << ".";
				else if (x - (n - 2 * k + 1) & 1)
					cout << ".";
				else
					cout << "X";
			}
			else {
				if (x <= n - 2 * k)
					cout << ".";
				else if (x - (n - 2 * k) & 1)
					cout << ".";
				else
					cout << "X";
			}
		}
	}
	cout << endl;
}
