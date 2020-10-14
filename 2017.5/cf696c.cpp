#include <bits/stdc++.h>

long long MOD = 1e9 + 7;
long long qpow(long long a, long long p) {
	a = a % MOD;
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
int k, p;
int main() {
	std::cin >> k;
	long long a = 1;
	int e = 1;
	for(int i = 0; i < k; i++) {
		long long x;
		scanf("%lld", &x);
		if(x % 2 == 0) e = 0;
		x %= (MOD - 1);
		a = (a * x) % (MOD - 1);
	}
	long long up, low;
	if(a == 0) a = MOD - 1;
	if(!e) {
		up = (1 + qpow(2, a - 1)) * qpow(3, MOD - 2) % MOD;
	}else {
		up = (qpow(2, a - 1) - 1 + MOD) * qpow(3, MOD - 2) % MOD;
	}
	low = qpow(2, a - 1);
	printf("%lld/%lld",up, low);
	return 0;
}
