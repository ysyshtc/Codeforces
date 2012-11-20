#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int a, b;

int main() {
	scanf("%d %d", &a, &b);
	int p = 6 - max(a, b) + 1, q = 6;
	int d = gcd(p, q);
	p /= d;
	q /= d;
	printf("%d/%d\n", p, q);
}
