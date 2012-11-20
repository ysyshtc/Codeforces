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

long long ans, x;
int n;

int main(int argc, char* argv[])
{
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> x;
		ans += (i + 1) * (x - 1);
	}
	cout << ans + n << endl;
}
