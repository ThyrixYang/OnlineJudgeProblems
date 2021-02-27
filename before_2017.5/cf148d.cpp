#include <bits/stdc++.h>

const int MAXN = 1005;
double dp[MAXN][MAXN][2];
int vis[MAXN][MAXN][2];
double DP(int w, int b, int k) {
	if(w < 0 || b < 0 || k < 0) return 0;
	if(vis[w][b][k]) return dp[w][b][k];
	if(w + b == 0) {
		if(k == 1) return 1;
		else return 0;
	}
	vis[w][b][k] = 1;
	double ans = 0;
	if(k == 0) {
		double tw = 1.0 * w / (w + b);
		double tb = 1.0 * b / (w + b);
		ans = tw + (1 - DP(w, b - 1, 1)) * tb;
	} else {
		if(w + b <= 2) return 1;
		double tw = 1.0 * w / (w + b);
		ans = tw;
		ans += (1 - tw) * (1 - DP(w, b - 2, 0)) * ((double)b - 1) / (w + b - 1);
		ans += (1 - tw) * (1 - DP(w - 1, b - 1, 0)) * ((double)w) / (w + b - 1);
	}
	dp[w][b][k] = ans;
	return ans;
}
int w, b;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> w >> b;
	printf("%.15f\n", DP(w, b, 0));
	return 0;	
}
