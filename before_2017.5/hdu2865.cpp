#include <bits/stdc++.h>

const long long MOD = 1e9 + 7;
const int maxn=2;
struct Matrix{
	long long a[maxn][maxn];
	Matrix(){memset(a,0,sizeof a);}
	Matrix operator * (Matrix b){
		Matrix ans;
		for(int i=0;i<maxn;i++)
			for(int j=0;j<maxn;j++)
				for(int k=0;k<maxn;k++)
					ans.a[i][j]=(ans.a[i][j]+a[i][k]*b.a[k][j] % MOD) % MOD;
		return ans;
	}
};
Matrix qpow(Matrix a,long long p){
	Matrix ans;
	for(int i = 0;i < maxn; i++) ans.a[i][i] = 1;
	while(p > 0){
		if(p & 1) ans = ans * a;
		a = a * a;
		p >>= 1;
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
long long inv(long long x) {
	return qpow(x, MOD - 2);
}
long long cal(long long x, long long c) {
	Matrix t;
	t.a[0][0] = c - 2; t.a[0][1] = c - 1;
	t.a[1][0] = 1;     t.a[1][1] = 0;
	t = qpow(t, x - 1);
	return t.a[0][1] * c % MOD;
}
long long phi(long long x) {
	long long ans = 1;
	for(long long d = 2; d * d <= x; d++) {
		if(x % d == 0) {
			x /= d;
			ans = ans * (d - 1);
			while(x % d == 0) {
				x /= d;
				ans = ans * d;
			}
		}
	}
	if(x > 1) ans *= x - 1;
	return ans;
}
long long n, k;
int main() {
	while(scanf("%lld%lld", &n, &k) != EOF) {
		long long ans = 0;
		for(int d = 1; d * d <= n; d++) {
			if(n % d == 0) {
				ans = (ans +phi(n / d) * cal(d, k - 1)) % MOD;
				if(d * d != n) {
					ans = (ans + phi(n / (n / d)) * cal(n / d, k - 1)) % MOD;
				}
			}
		}
		printf("%lld\n", ans * k % MOD * inv(n) % MOD);
	}
	return 0;
}
