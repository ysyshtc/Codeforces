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

const int MAXQ = 1111111;

struct Node {
	int x, y, t;
	Node() {}
	Node(int _x, int _y, int _t = 1) : x(_x), y(_y), t(_t) {}
} que[MAXQ], now, nx;
const Node orien[9] = {Node(0, 0), Node(0, 1), Node(0, -1), Node(1, 0), Node(-1, 0), Node(-1, 1), Node(-1, -1), Node(1, 1), Node(1, -1)};

char a[10][10];
bool ans, able[8 * 8 * 8][8][8];

inline Node operator+ (const Node &a, const Node &b) {
	return Node(a.x + b.x, a.y + b.y, a.t + b.t);
}

inline bool out_range(const Node &a) {
	return a.x < 0 || a.y < 0 || a.x > 7 || a.y > 7;
}

int main(int argc, char* argv[]) {
	for (int i = 0; i < 8; ++i)
		scanf("%s", a[i]);
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			if (a[i][j] == 'S') {
				able[1][i][j] = true;
				for (int p = i + 1; p < 8; ++p) {
					able[p - i + 1][p][j] = true;
					able[p - i][p][j] = true;
				}
			}
	que[1] = Node(7, 0, 0);
	for (int fore = 0, rear = 1; !ans && fore++ < rear; ) {
		now = que[fore];
		for (int i = 0; i < 9; ++i) {
			nx = now + orien[i];
			if (out_range(nx) || able[nx.t][nx.x][nx.y])
				continue;
			if (nx.x == 0 && nx.y == 7)
				ans = true;
			able[nx.t][nx.x][nx.y] = true;
			que[++rear] = nx;
		}
	}
	if (ans)
		printf("WIN\n");
	else
		printf("LOSE\n");
}
