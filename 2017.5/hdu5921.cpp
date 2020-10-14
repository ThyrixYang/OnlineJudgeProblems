#include <bits/stdc++.h>

const long long MOD = 1e9 + 7;
#define fs first
#define se second
typedef std::pair<long long, long long> P;
P dp[70][2][2];
int T;
long long N;
int bs[70], bh;
int vis[70][2][2];
void getbs(long long x) {
	bh = 0;
	while(x > 0) {
		bs[bh++] = (x & 1);
		x >>= 1;
	}
}
P DP(long long p, int up, int dif) {
	if(p == -1) return P(1, 0);
	if(vis[p][up][dif]) return dp[p][up][dif];
	vis[p][up][dif] = 1;
	long long& ans = dp[p][up][dif].se;
	long long& cnt = dp[p][up][dif].fs;
	ans = 0;
	cnt = 0;
	for(int x = 0; x < 2; x++) {
		for(int y = 0; y < 2; y++) {
			if(up && x > bs[p]) break;
			if(!dif && y > x) continue;
			int d = (dif || (x != y));
			P res;
			if(up && x == bs[p]) {
				res = DP(p - 1, 1, d);
			} else {
				res = DP(p - 1, 0, d);
			}
			ans += (res.se + res.fs * (x + y) * d % MOD) % MOD;
			ans %= MOD;
			cnt += res.fs;
			cnt %= MOD;
		}
	}
	return dp[p][up][dif];
}
long long cal(long long n) {
	getbs(n);
	std::memset(vis, 0, sizeof vis);
	return DP(bh - 1, 1, 0).se;
}
int cas = 0;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		scanf("%lld", &N);
		printf("Case #%d: %lld\n", ++cas, cal(N));
	}
	return 0;
}
