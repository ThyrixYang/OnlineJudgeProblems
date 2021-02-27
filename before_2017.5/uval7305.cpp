#include <bits/stdc++.h>

const int MAXN = 1005;
int T, N, L;
int p[MAXN], r[MAXN];
int cas = 0;
int dp[MAXN][MAXN];
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		printf("Case %d: ", ++cas);
		std::cin >> N >> L;
		for(int i = 0; i < N + 3; i++) {
			for(int j = 0; j < N + 3; j++) {
				dp[i][j] = -1;
			}
		}
		for(int i = 0; i <= N + 1; i++) scanf("%d", &p[i]);
		for(int i = 0; i <= N; i++) scanf("%d", &r[i]);
		dp[0][0] = p[0];
		for(int i = 1; i <= N + 1; i++) {
			for(int j = 0; j <= N + 1; j++) {
				if(j > 0) {
					if(dp[i - 1][j - 1] >= 0) {
						dp[i][j] = std::max(dp[i][j], 
									std::min(dp[i - 1][j - 1] + r[i - 1], p[i]));
					}
				}
				if(dp[i - 1][j] >= 0) {
					dp[i][j] = std::max(dp[i][j], 
							std::min(dp[i - 1][j] + std::min(r[i - 1], L), p[i]));
				}
			}
		}
		int ans = -1;
		for(int i = 0; i <= N + 1; i++) {
			if(dp[N + 1][i] >= p[N + 1]) {
				ans = i;
				break;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
