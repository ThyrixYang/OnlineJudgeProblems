#include <bits/stdc++.h>

const int maxn = 305;
const int inf = 1e7;
int n;
int G[maxn][maxn];
int dp[maxn][maxn];
int t_dp[10][maxn][maxn];

long long ans = 0;
void solve(int l, int r, int dep) {
	if(r - l == 1) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				if(i != l && j != l) {
					ans += dp[i][j] >= inf ? -1 : dp[i][j];
				}
			}
		}
		return ;
	}
	memcpy(t_dp[dep], dp, sizeof dp);
	int mid = (r + l) >> 1;
	for(int k = l; k < mid; k++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j]);
			}
		}
	}
	solve(mid, r, dep + 1);
	memcpy(dp, t_dp[dep], sizeof dp);
	for(int k = mid; k < r; k++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j]);
			}
		}
	}
	solve(l, mid, dep + 1);
}
int main() {
	
	std::cin >> n;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			scanf("%d", &G[i][j]);
			if(G[i][j] == -1) G[i][j] = inf;
			dp[i][j] = G[i][j];
		}
	}
	solve(1, n + 1, 0);
	std::cout << ans << std::endl;
	return 0;
}
