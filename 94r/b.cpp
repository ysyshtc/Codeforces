#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

const int MAXN = 111111;
const int MAXD = 21;

int next[MAXN], sa[MAXN], _sa[MAXN], rank[MAXN], n, cnt[256], h[MAXN], st[MAXN][MAXD], high_bit[MAXN], task, id, height[MAXN], it, p;
char s[MAXN];
PII _rank[MAXN];
ll part[MAXN], k, sum;

inline ll calc(int l, int r, int c) {
    if (l == 0) return part[r] - ll(r + 1) * c;
    return part[r] - part[l - 1] - ll(r - l + 1) * c;
}

inline int get_min(int l, int r) {
    int p = high_bit[r - l + 1];
    return min(st[l][p], st[r - (1 << p) + 1][p]);
}

inline int get_next(int it, int l) {
    int lower = it, upper = n - 1, mid;
    while (lower < upper) {
        mid = (lower + upper + 1) / 2;
        if (get_min(it + 1, mid) < l + 1)
            upper = mid - 1;
        else
            lower = mid;
    }
    return lower;
}

int main() {
    for (int i = 2; i < MAXN; ++i)
        high_bit[i] = high_bit[i >> 1] + 1;
    scanf("%s", s);
    cin >> k;
    memset(cnt, 0, sizeof cnt);
    n = strlen(s);
    if (ll(n) * (n + 1) / 2 < k) {
    	puts("No such line.");
    	return 0;
	}
    rank[n] = -1;
    for (int i = 0; i < n; ++i)
        ++cnt[s[i]];
    for (int i = 0; i < 255; ++i)
        cnt[i + 1] += cnt[i];
    for (int i = 0; i < n; ++i)
        rank[i] = cnt[s[i] - 1];
    for (int i = 0; i < n; ++i)
        sa[--cnt[s[i]]] = i;
    for (int del = 1; del < n; del *= 2) {
        for (int i = 0; i < n; ++i)
            next[i] = i, _sa[i] = sa[i] - del;
        for (int i = n - del; i < n; ++i)
            sa[next[rank[i]]++] = i;
        for (int i = 0; i < n; ++i)
            if (_sa[i] >= 0)
                sa[next[rank[_sa[i]]]++] = _sa[i];
        for (int i = 0; i < n; ++i)
            _rank[i] = PII(rank[i], rank[min(i + del, n)]);
        rank[sa[0]] = 0;
        for (int i = 1; i < n; ++i)
            rank[sa[i]] = _rank[sa[i]] != _rank[sa[i - 1]] ? i : rank[sa[i - 1]];
    }
    for (int i = 0; i < n; ++i)
        if (!rank[i])
            h[i] = 0;
        else {
            int &k = h[i], j = sa[rank[i] - 1];
            k = i ? max(h[i - 1] - 1, 0) : 0;
            while (max(i, j) + k < n && s[i + k] == s[j + k]) ++k;
        }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < MAXD; ++j)
            st[i][j] = 0;
    for (int i = 0; i < n; ++i) {
        height[i] = h[sa[i]];
        st[i][0] = height[i];
    }
    for (int i = 1; i < MAXD; ++i)
        for (int j = 0; j <= n - (1 << i); ++j)
            st[j][i] = min(st[j][i - 1], st[j + (1 << i >> 1)][i - 1]);
    for (int i = 0; i < n; ++i)
        part[i] = n - sa[i];
    for (int i = 1; i < n; ++i)
        part[i] += part[i - 1];
    it = 0;
    for (int i = 0; k > 0; ++i) {
        while (true) {
            p = get_next(it, i);
            sum = calc(it, p, i);
            if (sum < k) {
                it = p + 1;
                k -= sum;
            }
            else {
                k -= p - it + 1;
                break;
            }
        }
        printf("%c", s[sa[it] + i]);
    }
    printf("\n");
}
