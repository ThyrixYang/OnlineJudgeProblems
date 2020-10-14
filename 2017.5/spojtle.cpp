#include <bits/stdc++.h>

const int MOD = 1e9;
void ma(int &a, int b) {
	a += b;
	if(a >= MOD) a -= MOD;
	if(a < 0) a += MOD;
}
void FMT(int *f, int n, int on) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < (1 << n); j++) {
			if(j & (1 << i)) continue;
			ma(f[j ^ (1 << i)], f[j] * on);
		}
	}
}
int c[100];
int N, M, T;
int dp[1 << 16];
int X;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		std::cin >> N >> M;
		X = (1 << M) - 1;
		for(int i = 0; i < N; i++) scanf("%d", &c[i]);
		for(int i = 0; i < (1 << M); i++) {
			dp[i] = 1;
		}
		for(int x = c[0]; x < (1 << M); x += c[0]) dp[x] = 0;
		dp[0] = 0;
		for(int i = 0; i < N - 1; i++) {
			FMT(dp, M, 1);
			for(int j = 0; j < (1 << M); j++) {
				if((X ^ j) >= j) continue;
				std::swap(dp[X ^ j], dp[j]);
			}
			for(int x = c[i + 1]; x < (1 << M); x += c[i + 1]) {
				dp[x] = 0;
			}
			dp[0] = 0;
		}
		int ans = 0;
		for(int i = 0; i < (1 << M); i++) ma(ans, dp[i]);
		std::cout << ans << std::endl;
	}
	return 0;
}
