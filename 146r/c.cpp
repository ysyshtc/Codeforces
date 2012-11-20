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

const static int MAXC = 26;
struct State {
	static State *memory;
	State *go[MAXC], *link;
	int len, path;
	void init(int init_len = 0) {
		len = init_len; link = NULL; path = 0;
		memset(go, NULL, sizeof go);
	}
	State* next_state(State* start, int token) {
		State *it = this, *next = memory++;
		next->init(it->len + 1);
		while (it != NULL && it->go[token] == NULL) {
			it->go[token] = next;
			it = it->link;
		}
		if (it == NULL) {
			next->link = start;
			return next;
		}
		State *old = it->go[token];
		if (old->len == it->len + 1)
			next->link = old;
		else {
			State *split = memory++;
			memcpy(split, old, sizeof(State));
			split->len = it->len + 1;
			old->link = next->link = split;
			while (it != NULL && it->go[token] == old) {
				it->go[token] = split;
				it = it->link;
			}
		}
		return next;
	}
};

const static int MAX_MEM = 2111111;
void* pool = malloc(MAX_MEM * sizeof(State));// free(pool);
State* State::memory = (State*)pool;

int dfs(State* p) {
	if (p->path > 0)
		return p->path;
	int ret = -p->path;
	for (int i = 0; i < MAXC; ++i)
		if (p->go[i] != NULL)
			ret += dfs(p->go[i]);
	return p->path = ret;
}

pair<State*, State*> make_automaton(char* const s) {
	State *start = State::memory;
	State *last = State::memory++;
	start->init(0);
	int length = strlen(s);
	for (int i = 0; i < length; ++i)
		last = last->next_state(start, s[i] - 'a');
	for (State *travel = last; travel != NULL; travel = travel->link)
		travel->path = -1;
	dfs(start);
	return make_pair(start, last);
}

int main() {
	char buff[1111111];
	char query[211111];
	gets(buff);
	pair<State*, State*> solver = make_automaton(buff);
	int q = strlen(buff), cover = 0;
	for (int i = 0; i < q; ++i)
		cover |= 1 << buff[i] - 'a';
	for (scanf("%d\n", &q); q-- > 0; ) {
		gets(query);
		int length = strlen(query), mask = 0;
		for (int i = length; i < length + length; ++i) {
			query[i] = query[i - length];
			mask |= 1 << query[i] - 'a';
		}
		if ((mask & cover) != mask) {
			puts("0");
			continue;
		}
		int ret = 0;
		State* travel = solver.first, *match = NULL;
		for (int i = 0, j = 0; i < length; ++i) {
			for (; j < length + length && j - i < length; ++j) {
				int token = query[j] - 'a';
				while (travel->go[token] == NULL) {
					travel = travel->link;
					i = j - travel->len;
				}
				travel = travel->go[token];
			}
			if (j - i == length) {
				if (travel == match)
					break;
				if (match == NULL)
					match = travel;
				ret += travel->path;
				int minlen = travel->link->len + 1;
				if (minlen == length)
					travel = travel->link;
			}
		}
		printf("%d\n", ret);
	}
}

