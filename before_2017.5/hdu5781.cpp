#include <bits/stdc++.h>

const int MAXN = 2005;
int K, W;
double dp[MAXN][MAXN];
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d%d", &K, &W) != EOF) {
		for(int i = 1; i <= K; i++) {
			for(int j = 1; j <= W; j++) {
				int l = 0, r = i - 1;
				while(r - l > 1) {
					int mid = (r + l) >> 1;
					double t1 = dp[mid][j - 1] * 1.0 * mid / i + dp[
				}
			}
		}
	}
	return 0;
}
