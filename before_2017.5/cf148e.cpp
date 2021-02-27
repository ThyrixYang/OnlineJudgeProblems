#include <bits/stdc++.h>

int n, m;
int val[105][105];
int tmp[105];
int dp[10005];
int main() {
	freopen("./in", "r", stdin);
	std::cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		int k;
		scanf("%d", &k);
		for(int j = 1; j <= k; j++) {
			scanf("%d", &tmp[j]);
			tmp[j] += tmp[j - 1];
		}
		for(int j = 1; j <= k ; j++) {
			for(int p = 0; p <= j; p++) {
				val[i][j] = std::max(val[i][j], tmp[p] + tmp[k] - tmp[k - (j - p)]);
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = m; j >= 1; j--) {
			for(int k = 1; k <= 100 && j - k >= 0; k++) {
				dp[j] = std::max(dp[j], dp[j - k] + val[i][k]);
			}
		}
	}
	printf("%d\n", dp[m]);
	return 0;
}
