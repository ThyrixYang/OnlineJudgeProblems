#include <bits/stdc++.h>

long long f[100];
void init() {
	f[0] = 1;
	f[1] = 1;
	for(int i = 2; i < 100; i++) {
		f[i] = f[i - 1] + f[i - 2];
	}
}
long long getNear(long long x) {
	int p = std::lower_bound(f + 1, f + 89, x) - f;
	long long d = 1e18, ans = 0;
	for(int i = p - 1; i <= p + 1; i++) {
		if(std::abs(f[i] - x) < d) {
			d = std::abs(f[i] - x);
			ans = f[i];
		}
	}
	return ans;
}
#define chl ((o << 1))
#define chr ((o << 1) | 1)
#define mi ((r + l) >> 1)
const int MAXN = 5e5;
long long val[MAXN];
int lab[MAXN];
long long Min[MAXN], Max[MAXN];
long long chg[MAXN];
int lab2[MAXN];
void build(int o, int l, int r) {
	lab2[o] = Min[o] = val[o] = Max[o] = lab[o] = 0;
	if(r - l <= 1) return;
	build(chl, l, mi);
	build(chr, mi, r);
}
void up(int o, int l, int r) {
	Min[o] = std::min(Min[chl], Min[chr]);
	Max[o] = std::max(Max[chr], Max[chl]);
	val[o] = val[chl] + val[chr];
}
void push(int o, int l, int r) {
	if(r - l <= 1 || (!lab[o] && !lab2[o])) return;
	if(lab[o]) {
		lab[o] = 0;
		lab[chl] = lab[chr] = 1;
		chg[chl] = chg[chr] = Max[chl] = Max[chr] = Min[chr] = Min[chl] = chg[o];
		val[chl] = chg[o] * (mi - l);
		val[chr] = chg[o] * (r - mi);
	}
	if(lab2[o]) lab2[chl] = lab2[chr] = 1;
}
void change(int o, int a, int b, int l, int r) {
	if(b <= l || a >= r) return;
	push(o, l, r);
	if(l >= a && r <= b) {
		if(lab2[o]) return;
		lab2[o] = 1;
		long long x = getNear(Min[o]);
		if(x == getNear(Max[o])) {
			val[o] = x * (r - l);
			chg[o] = x;
			Min[o] = Max[o] = x;
			lab[o] = 1;
			return;
		}
	}
	change(chl, a, b, l, mi);
	change(chr, a, b, mi, r);
	up(o, l, r);
}
void add(int o, int p, int l, int r, long long x) {
	push(o, l, r);
	lab2[o] = 0;
	if(r - l <= 1) {
		val[o] += x;
		Min[o] = Max[o] = val[o];
		return;
	}
	if(p < mi) add(chl, p, l, mi, x);
	else add(chr, p, mi, r, x);
	up(o, l, r);
}
long long sum(int o, int a, int b, int l, int r) {
	if(a >= r || b <= l) return 0;
	push(o, l, r);
	if(l >= a && r <= b) return val[o];
	return sum(chl, a, b, l, mi) + sum(chr, a, b, mi, r);
}
int n, m;
int main() {
	freopen("./in", "r", stdin);
	init();
	while(scanf("%d%d", &n, &m) != EOF) {
		build(1, 1, n + 1);
		while(m--) {
			int t;
			scanf("%d", &t);
			if(t == 1) {
				int p, d;
				scanf("%d%d", &p, &d);
				add(1, p, 1, n + 1, d);
			}else if(t == 2) {
				int l, r;
				scanf("%d%d", &l, &r);
				printf("%lld\n", sum(1, l, r + 1, 1, n + 1));
			}else {
				int l, r;
				scanf("%d%d", &l, &r);
				change(1, l, r + 1, 1, n + 1);
			}
		}
	}
	return 0;
}
