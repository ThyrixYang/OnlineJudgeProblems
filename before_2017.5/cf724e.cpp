#include <bits/stdc++.h>

const int MAXN = 1e4 + 30;
long long N, C;
int p[MAXN], s[MAXN];
long long dp[2][MAXN];
int main() {
	freopen("in", "r", stdin);
	std::cin >> N >> C;
	for(int i = 1; i <= N; i++) {
		scanf("%d", &p[i]);
	}
	for(int i = 1; i <= N; i++) {
		scanf("%d", &s[i]);
	}
	for(int i = 1; i < MAXN; i++) {
		dp[0][i] = 1e18;
	}
	for(int i = 1; i <= N; i++) {
		int f = (i & 1);
		int d = (f ^ 1);
		for(int j = 0; j <= N; j++) {
			dp[f][j] = dp[d][j] + p[i] + C * j;
			if(j > 0) dp[f][j] = std::min(dp[f][j], dp[d][j - 1] + s[i]);
		}
	}
	int t = (N & 1);
	long long ans = 1e18;
	for(int i = 0; i <= N; i++) {
		ans = std::min(ans, dp[t][i]);
	}
	std::cout << ans << std::endl;
	return 0;
}