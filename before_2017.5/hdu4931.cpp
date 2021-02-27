#include <bits/stdc++.h>

const int MAXN = 5e5;
const long long MOD = 1e9 + 7;
long long qpow(long long a, long long p) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
int n;
int a[MAXN], b[MAXN];
int dic[MAXN], dh;

long long val[MAXN];
long long mul[MAXN];
int lab[MAXN];
#define chl ((o << 1))
#define chr ((o << 1) | 1)
void push(int o, int l, int r) {
	if(r - l <= 1 || !lab[o]) return;
	lab[o] = 0;
	lab[chl] = lab[chr] = 1;
	mul[chl] = (mul[chl] * mul[o]) % MOD;
	mul[chr] = (mul[chr] * mul[o]) % MOD;
	mul[o] = 1;
}
void up(int o, int l, int r) {
	if(r - l <= 1)return;
	val[o] = (val[chl] + val[chr]) % MOD;
}
void change(int o, int a, int b, int l, int r, long long x) {
	if(b <= l || a >= r) return;
	if(l >= a && r <= b) {
		val[o] = val[o] * x % MOD;
		mul[o] = mul[o] * x % MOD;
		lab[o] = 1;
		return;
	}
	change(chl, a, b, l, mi, x);
	change(chr, a, b, mi, r, x);
	up(o, l, r);
}
void build(int o, int l, int r) {
	if(r - l <= 1) {
	}

}
int main() {
	while(scanf("%d", &n) != EOF) {
		dh = 0;
		for(int i = 0; i < n; i++) {
			scanf("%d%d", &a[i], &b[i]);
			dic[dh++] = b[i];
		}
		std::sort(dic, dic + dh);
		dh = std::unique(dic, dic + dh) - dh;
		
	}
	return 0;
}
