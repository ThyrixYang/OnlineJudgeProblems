#include <bits/stdc++.h>

const long long MOD = 1e6 + 3;
long long fac[MOD];
long long inv[MOD];
long long n, c;
long long qpow(long long a, long long p) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
int main() {
	fac[0] = inv[0] = 1;
	for(int i = 1; i < MOD; i++) {
		fac[i] = fac[i - 1] * i % MOD;
		inv[i] = qpow(fac[i], MOD - 2);
	}
	std::cin >> n >> c;
	long long ans = 0;
	for(int w = 1; w <= n; w++) {
		long long res = fac[w + c - 1] * inv[c - 1] % MOD * inv[w] % MOD;
		ans = (ans + res) % MOD;
	}
	std::cout << ans;
	return 0;
}
