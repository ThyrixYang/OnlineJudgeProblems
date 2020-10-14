#include <bits/stdc++.h>

const int MAXN = 2e5;
const int MAXO = 5e6;
int ch[MAXN][26];
char s[MAXN];
int n, q;
int sz;
int a[MAXN], ah;
int f[MAXN], t[MAXN];

struct Node {
	int val;
	int ls, rs;
}T[MAXO];
int oh;
#define mi ((l + r) >> 1)
void add(int &o, int p, int l, int r, int x) {
	T[++oh] = T[o];
	o = oh;
	T[o].val += x;
	if(r - l <= 1) return;
	if(p < mi) add(T[o].ls, p, l, mi, x);
	else add(T[o].rs, p, mi, r, x);
}
int sum(int o, int a, int b, int l, int r) {
	if(a >= r || b <= l) return 0;
	if(l >= a && r <= b) return T[o].val;
	return sum(T[o].ls, a, b, l, mi) + sum(T[o].rs, a, b, mi, r);
}
void insert(int id) {
	int len = strlen(s);
	int v = 0;
	f[id] = ah;
	for(int i = 0; i < len; i++) {
		int c = s[i] - 'a';
		if(!ch[v][c]) {
			sz++;
			std::memset(ch[sz], 0, sizeof ch[sz]);
			ch[v][c] = sz;
		}
		v = ch[v][c];
		a[ah++] = v;
	}
	t[id] = ah;
}
int last[MAXN], root[MAXN];
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d", &n) != EOF) {
		std::memset(ch[0], 0, sizeof ch[0]);
		oh = sz = 0;
		ah = 1;
		for(int i = 1; i <= n; i++) {
			scanf("%s", s);
			insert(i);
		}
		std::memset(last, -1, sizeof last);
		for(int i = 1; i < ah; i++) {
			root[i] = root[i - 1];
			if(last[a[i]] != -1) {
				add(root[i], last[a[i]], 1, ah, -1);
			}
			add(root[i], i, 1, ah, 1);
			last[a[i]] = i;
		}
		int q;
		int Ans = 0;
		scanf("%d", &q);
		while(q--) {
			int l, r;
			scanf("%d%d", &l, &r);
			l = (Ans + l) % n + 1;
			r = (Ans + r) % n + 1;
			if(l > r) std::swap(l, r);
			int res = sum(root[t[r] - 1], f[l], ah, 1, ah);
			printf("%d\n", res);
			Ans = res;
		}
	}
	return 0;
}
