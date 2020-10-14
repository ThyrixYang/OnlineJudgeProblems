#include <bits/stdc++.h>

const int MAXN = 2e5;
int n;
std::string s[MAXN][2];
int c[MAXN];
long long dp[MAXN][2];
void ma(long long &a, long long b) {
	if(b == -1) return;
	if(a == -1) a = b;
	else a = std::min(a, b);
}
int main() {
	freopen("./in", "r", stdin);
	std::memset(dp, -1, sizeof dp);
	std::cin >> n;
	for(int i = 0; i < n; i++) scanf("%d", &c[i]);
	dp[0][0] = 0, dp[0][1] = c[0];
	for(int i = 0; i < n; i++) {
		std::cin >> s[i][0];
		s[i][1] = s[i][0];
		std::reverse(s[i][1].begin(), s[i][1].end());
		if(i == 0) continue;
		if(dp[i - 1][0] != -1) {
			if(s[i][0] >= s[i - 1][0]) ma(dp[i][0], dp[i - 1][0]);
			if(s[i][1] >= s[i - 1][0]) ma(dp[i][1], dp[i - 1][0] + c[i]);
		} 
		if(dp[i - 1][1] != -1) {
			if(s[i][1] >= s[i - 1][1]) ma(dp[i][1], dp[i - 1][1] + c[i]);
			if(s[i][0] >= s[i - 1][1]) ma(dp[i][0], dp[i - 1][1]);
		}
	}
	long long ans = -1;
	ma(ans, dp[n - 1][0]);
	ma(ans, dp[n - 1][1]);
	std::cout << ans << std::endl;
	return 0;
}
