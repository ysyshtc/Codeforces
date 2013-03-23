#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>

using namespace std;

const int MAXN = 111111;

int n;
bool zero;
char s[MAXN];

int main() {
	scanf("%s", s);
	n = strlen(s);
	for (int i = 0; i < n; ++i)
		if (!zero && (s[i] == '0' || i == n - 1))
			zero = true;
		else
			printf("%c", s[i]);
	puts("");
}

