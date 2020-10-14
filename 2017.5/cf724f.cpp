#include <bits/stdc++.h>

const int MAXN = 1026;
typedef std::pair<long long, long long> P;
std::map<P, long long> M;
long long MOD;
long long qpow(long long a, long long p) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = (ans * a) % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
int N, D;
long long dp[MAXN][11][MAXN];
long long inv[200];
long long C(long long n, long long k) {
	std::map<P, long long>::iterator it = M.find(P(n, k));
	if(it != M.end()) return it->second;
	n %= MOD;
	long long ans = 1;
	for(long long i = 0; i < k; i++) {
		ans = (ans * (n - i + MOD)) % MOD;
	}
	ans = ans * inv[k] % MOD;
	return M[P(n, k)] = ans;
}
int main() {
	freopen("in.txt", "r", stdin);
	std::cin >> N >> D >> MOD;
	if(N == 1) {
		puts("1");
		return 0;
	}
	inv[0] = 1;
	for(int i = 1; i <= 20; i++) {
		inv[i] = inv[i - 1] * qpow(i, MOD - 2) % MOD;
	}
	for(int i = 0; i <= N; i++) {
		dp[1][D - 1][i] = 1;
		dp[1][0][i] = 1;
	}
	for(int i = 2; i <= N; i++) {
		for(int j = 1; j <= D; j++) {
			for(int k = 1; k <= N; k++) {
				dp[i][j][k] = dp[i][j][k - 1];
				for(int t = 1; t * k <= i && t <= j; t++) {
					dp[i][j][k] += dp[i - k * t][j - t][k - 1] * 
						C(dp[k][D - 1][k - 1] + t - 1, t) % MOD;
					if(dp[i][j][k] >= MOD) dp[i][j][k] -= MOD;
				}
			}
		}
	}
	long long ans = dp[N][D][(N + 1) / 2 - 1];
	long long x = dp[N / 2][D - 1][N / 2 - 1];
	if(N % 2 == 0) ans += (x * x % MOD + x) % MOD * inv[2] % MOD;
	ans %= MOD;
	std::cout << ans << std::endl;
	return 0;
}
