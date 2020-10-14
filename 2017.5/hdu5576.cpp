#include <bits/stdc++.h>

const int MOD = 1e9 + 7;
long long qpow(long long a, long long p) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}

long long fac[100], inv[100];
long long C[100][100];
long long p10[200];
int T, cas;
char s[100];
int k, n;
long long dp[2][60][60][60];
long long sumj[60][60];
long long sumi[60][60];
long long sumy[60][60];
inline void ma(long long &a, const long long &b) {
	a += b;
	if(a >= MOD) a -= MOD;
}
inline void de(long long &a, const long long &b) {
	a -= b;
	if(a < 0) a += MOD;
}
int main() {
	freopen("./in", "r", stdin);
	fac[0] = inv[0] = 1;
	for(int i = 1; i < 100; i++) {
		fac[i] = fac[i - 1] * i % MOD;
		inv[i] = qpow(fac[i], MOD - 2);
		for(int j = 0; j <= i; j++)
			C[i][j] = fac[i] * inv[j] % MOD * inv[i - j] % MOD;
	}
	p10[0] = 1;
	for(int i = 1; i < 200; i++) p10[i] = p10[i - 1] * 10 % MOD;
	std::cin >> T;
	while(T--) {
		printf("Case #%d: ", ++cas);
		scanf("%d", &k);
		scanf("%s", s);
		n = strlen(s);
		std::memset(dp, 0, sizeof dp);
		std::memset(sumj, 0, sizeof sumj);
		std::memset(sumi, 0, sizeof sumi);
		int p = 0;
		for(int i = 0; i < n; i++) {
			if(s[i] == '*') p = i;
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(i == j) continue;
				if(i == p || j == p) continue;
				dp[0][p][i][j] = (s[i] - '0') * (s[j] - '0');
			}
		}
		for(int x = 1; x <= k; x++) {
			int f = x & 1;
			std::memset(sumi, 0, sizeof sumi);
			std::memset(sumj, 0, sizeof sumj);
			std::memset(sumy, 0, sizeof sumy);
			for(int i = 0; i < n; i++) 
				for(int j = 0; j < n; j++) 
					for(int z = 0; z < n; z++) {
						ma(sumi[i][j], dp[f ^ 1][i][z][j]);
						ma(sumj[i][j], dp[f ^ 1][i][j][z]);
						ma(sumy[i][j], dp[f ^ 1][z][i][j]);
					}
			for(int y = 0; y < n; y++) {
				for(int i = 0; i < n; i++) { 
					for(int j = 0; j < n; j++) {
						dp[f][y][i][j] = 0;
						long long &res = dp[f][y][i][j];
						if(i == j) continue;
						if(i != y && j != y) {
							ma(res, dp[f ^ 1][y][j][i]);
							ma(res, dp[f ^ 1][i][y][j]);
							ma(res, dp[f ^ 1][j][i][y]);
							ma(res, dp[f ^ 1][y][j][i] * C[n - 3][2] % MOD);
							ma(res, sumj[y][i]);
							ma(res, sumi[y][j]);
							ma(res, sumy[i][j]);
							de(res, dp[f ^ 1][y][i][j] * 3 % MOD);
						}
					}
				}
			}
		}
		long long ans = 0;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < i; j++) {
				for(int z = i + 1; z < n; z++) {
					ma(ans, dp[k & 1][i][j][z] * p10[i - j - 1 + n - z - 1] % MOD);
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
