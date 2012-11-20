#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

string s;

int main() {
	cin >> s;
	int n = (int)s.length(), ret = 0;
	for (int i = 0; i < n; ++i)
		if (s[i] == '1')
			ret += 1 << n - i - 1;
		else if (s[i] > '1') {
			ret += (1 << n - i) - 1;
			break;
		}
	cout << ret << endl;
}
