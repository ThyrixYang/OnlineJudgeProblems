#include <bits/stdc++.h>

const long long MOD = 1e9 + 7;
const long long INV = (MOD + 1) >> 1;
const int MAXN = 2e6 + 300;
void madd(long long &a, long long b) {
	a += b;
	if(a >= MOD) a -= MOD;
	if(a < 0) a += MOD;
}
void FWT(long long *f, int n, int on) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < (1 << n); j++) {
			if(j & (1 << i)) continue;
			//or
			madd(f[j | (1 << i)], on * f[j]);
			//xor
			/*long long l = f[j], r = f[j | (1 << i)];
			f[j] = (l + r) % MOD, f[j | (1 << i)] = (l - r + MOD) % MOD;
			if(on == -1) f[j] = f[j] * INV % MOD;*/
		}
	}
}
int N;
int a[MAXN];
long long b[MAXN];
int fun(int x) {
	int ans = 0;
	while(x > 0) {
		if(x & 1) ans++;
		x >>= 1;
	}
	return ans;
}
long long qpow(long long a, long long p) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
int val = (1 << 20) - 1;
int main() {
	freopen("in", "r", stdin);
	std::cin >> N;
	for(int i = 0; i < N; i++) {
		scanf("%d", &a[i]);
		b[a[i] ^ val]++;
	}
	FWT(b, 20, 1);
	long long ans = 0;
	for(int i = 0; i < (1 << 20); i++) {
		//if(b[i] != 0) printf("%d %lld\n", i, b[i]);
		if(fun(i ^ val) % 2 == 0) madd(ans, qpow(2, b[i]));
		else madd(ans, -qpow(2, b[i]));
	}
	std::cout << ans << std::endl;
	return 0;
}
