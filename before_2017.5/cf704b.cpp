#include <bits/stdc++.h>

const int MAXN = 5005;
int n, s, e;
int x[MAXN];
int a[MAXN], b[MAXN], c[MAXN], d[MAXN];
long long dp[2][MAXN][2][2];
void ma(long long &a, long long x) {
	if(a == -1) {
		a = x;
		return;
	}
	a = std::min(a, x);
}
int main() {
	freopen("./in", "r", stdin);
	std::memset(dp, -1, sizeof dp);
	scanf("%d%d%d", &n, &s, &e);
	for(int i = 1; i <= n; i++) scanf("%d", &x[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &c[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &d[i]);
	int f = 0;
	if(s == 1) dp[1][0][1][0] = d[1];
	else if(e == 1) dp[1][0][0][1] = b[1];
	else dp[1][1][0][0] = d[1] + b[1];
	for(int i = 1; i < n; i++) {
		std::memset(dp[f], -1, sizeof dp[f]);
		for(int j = 0; j <= n; j++) {
			for(int k = 0; k < 2; k++) {
				for(int l = 0; l < 2; l++) {
					if(!(l || k || j)) continue;
					if(dp[f ^ 1][j][k][l] == -1) continue;
					//std::cout << i << " " << j << " " << k << " " << l << std::endl;
					long long len = ((long long)x[i + 1] - x[i]) * (2 * j + k + l);
					if(i + 1 == s) {
						ma(dp[f][j][k + 1][l], dp[f ^ 1][j][k][l] + len + d[i + 1]);
						if(j > 0) {
							ma(dp[f][j - 1][k + 1][l], 
									dp[f ^ 1][j][k][l] + len + c[i + 1]);
						}
						if(i + 1 == n && l && j == 0) 
							ma(dp[f][0][0][0], dp[f ^ 1][j][k][l] + len + c[i + 1]);
					} else if(i + 1 == e) {
						ma(dp[f][j][k][l + 1], dp[f ^ 1][j][k][l] + len + b[i + 1]);
						if(j > 0) {
							ma(dp[f][j - 1][k][l + 1],
									dp[f ^ 1][j][k][l] + len + a[i + 1]);
						}
						if(i + 1 == n && k && j == 0)
							ma(dp[f][0][0][0], dp[f ^ 1][j][k][l] + len + a[i + 1]);
					} else {
						ma(dp[f][j + 1][k][l], 
								dp[f ^ 1][j][k][l] + len + d[i + 1] + b[i + 1]);
						if(j) ma(dp[f][j - 1][k][l],
								dp[f ^ 1][j][k][l] + len + c[i + 1] + a[i + 1]);
						if(j || l) ma(dp[f][j][k][l],
								dp[f ^ 1][j][k][l] + len + c[i + 1] + b[i + 1]);
						if(k || j) ma(dp[f][j][k][l], 
								dp[f ^ 1][j][k][l] + len + a[i + 1] + d[i + 1]);
						if(i + 1 == n && j == 0 && k && l) ma(dp[f][0][0][0],
								dp[f ^ 1][j][k][l] + len + c[i + 1] + a[i + 1]);
									
					}
				}
			}
		}
		f ^= 1;
	}
	printf("%lld\n", dp[f ^ 1][0][0][0]);
	return 0;
}
