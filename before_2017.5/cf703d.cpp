#include <bits/stdc++.h>

const int MAXN = 1e6 + 300;
const int MAXO = MAXN * 5;
int n;
long long val[MAXO];
int sz = 0;
#define mi ((r + l) >> 1)
#define chl ((o << 1))
#define chr ((o << 1) | 1)
int a[MAXN];
int dic[MAXN], dh;
int last[MAXN];
int m;
void add(int o, int p, int l, int r, long long x) {
	val[o] ^= x;
	if(r - l <= 1) return;
	if(p < mi) add(chl, p, l, mi, x);
	else add(chr, p, mi, r, x);
}
long long sum(int o, int a, int b, int l, int r) {
	if(a >= r || b <= l) return 0;
	if(l >= a && r <= b) return val[o];
	return sum(chl, a, b, l, mi) ^ sum(chr, a, b, mi, r);
}
#define idx(x) (std::lower_bound(dic, dic + dh, x) - dic)
struct Node {
	int l, r;
	int id;
	bool operator < (const Node &C) const {
		return r < C.r;
	}
}Q[MAXN];
long long ans[MAXN];
int main() {
	freopen("./in", "r", stdin);
	std::cin >> n;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		dic[dh++] = a[i];
	}
	std::sort(dic, dic + dh);
	dh = std::unique(dic, dic + dh) - dic;
	scanf("%d", &m);
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &Q[i].l, &Q[i].r);
		Q[i].id = i;
	}
	std::sort(Q, Q + m);
	int j = 1;
	for(int i = 0; i < m; i++) {
		int l = Q[i].l, r = Q[i].r;
		while(j <= r) {
			int k = idx(a[j]);
			if(last[k] == 0) last[k] = j;
			else {
				add(1, last[k], 1, n + 1, a[j]);
				last[k] = j;
			}
			j++;
		}
		ans[Q[i].id] = sum(1, l, r + 1, 1, n + 1);
	}
	for(int i = 0; i < m; i++) {
		printf("%lld\n", ans[i]);
	}
	return 0;
}
