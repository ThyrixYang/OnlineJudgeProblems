#include <bits/stdc++.h>

const int MAXN = 2e5;
const long long MOD = 1e9 + 9;
long long qpow(long long a, long long p) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
int n, m;
int x[MAXN];
long long fac[MAXN];
long long inv[MAXN];
long long C(int n, int p) {
	return fac[n] * inv[n - p] % MOD * inv[p] % MOD;
}
int main() {
	inv[0] = fac[0] = 1;
	for(int i = 1; i < MAXN; i++) {
		fac[i] = fac[i - 1] * i % MOD;
		inv[i] = qpow(fac[i], MOD - 2);
	}
	freopen("./in", "r", stdin);
	while(scanf("%d%d", &n, &m) != EOF) {
		for(int i = 0; i < n; i++)
			scanf("%d", &x[i]);
		int l = 0, r = 0;
		for(int i = 0; i < n; i++) {
			if(x[i] == 0) continue;
			int dl, dr;
			if(x[i] + r <= m) {
				dr = r + x[i];
			}else if(x[i] + l <= m) {
				if((m - l - x[i]) % 2 == 0) dr = m;
				else dr = m - 1;
			}else {
				dr = m - (l + x[i] - m);
			}
			if(x[i] <= l) dl = l - x[i];
			else if(x[i] <= r) {
				if((x[i] - l) % 2 == 0) dl = 0;
				else dl = 1;
			}else {
				dl = x[i] - r;
			}
			l = dl, r = dr;
		}
		long long ans = 0;
		for(int i = l; i <= r; i += 2) {
			ans += C(m, i);
		}
		ans %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
}
