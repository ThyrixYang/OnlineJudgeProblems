#include <bits/stdc++.h>

const int MAXN = 100000 + 30;
long long L, R, K;
long long dp[20][MAXN][2];
int B;
std::vector<int> ne[MAXN][2];
int has[10];
void init() {
	for(int i = 0; i < B; i++) {
		ne[i][0].clear();
		ne[i][1].clear();
		int x = i;
		std::memset(has, 0, sizeof has);
		int f = 1;
		for(int j = 0; j < K - 1; j++) {
			if(has[x % 10]++ > 0) f = 0;
			x /= 10;
		}
		if(f) {
			for(int j = 0; j < 10; j++) {
				if(!has[j]) ne[i][0].push_back(j);
			}
		}
		f = 1;
		x = i;
		std::memset(has, 0, sizeof has);
		while(x > 0) {
			if(has[x % 10]++ > 0) f = 0;
			x /= 10;
		}
		if(f) {
			for(int j = 0; j < 10; j++) {
				if(!has[j]) ne[i][1].push_back(j);
			}
		}
	}
}
int a[20], ah = 0;
long long DP(int p, int mask, int up, int first) {
	if(!up && dp[p][mask][first] != -1) return dp[p][mask][first];
	if(p == ah) return 1;
	long long ans = 0;
	for(int i = 0; i < ne[mask][first].size(); i++) {
		int x = ne[mask][first][i];
		if(up && x > a[p]) break;
		int g = mask * 10 + x;
		ans += DP(p + 1, g % B, up && x == a[p], first && g / (B / 10) == 0);
	}
	if(!up) dp[p][mask][first] = ans;
	return ans;
}
long long cal(long long x) {
	ah = 0;
	while(x > 0) {
		a[ah++] = x % 10;
		x /= 10;
	}
	std::reverse(a, a + ah);
	std::memset(dp, -1, sizeof dp);
	return DP(0, 0, 1, 1);
}
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%lld%lld%lld\n", &L, &R, &K) != EOF) {
		B = 1;
		for(int i = 0; i < K - 1; i++) B *= 10;
		init();
		long long ansl = cal(L - 1);
		long long ansr = cal(R);
		printf("%lld\n", ansr - ansl);
	}
	return 0;
}
