#include <bits/stdc++.h>


using namespace std;
const long long MOD = 1e9 + 7;
long long qpow(long long a, long long p) {
	long long ans = 1;
	a %= MOD;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
const int MAXM = 2e5 + 44;
const int MAXN = 2005;
struct Point {
	int x, y;
	Point(int a = 0, int b = 0): x(a), y(b) {}
}p[MAXN];
bool cmp(const Point &a,const Point &b) {
	if(a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}
long long fac[MAXM], inv[MAXM];
long long C(int n, int k) {
	return fac[n] * inv[k] % MOD * inv[n - k] % MOD;
}
long long path(int x1, int y1, int x2, int y2) {
	return C(y2 - y1 + x2 - x1, x2 - x1);
}
long long rd[MAXN];
int N, M, K, S;
long long dp[MAXN][23];
int has11 = 0, hasnm = 0;
void ma(long long &a, long long b) {
	a += b;
	if(a >= MOD) a -= MOD;
	if(a < 0) a += MOD;
}
int main() {
	freopen("./in", "r", stdin);
	cin >> N >> M >> K >> S;
	rd[0] = S;
	fac[0] = inv[0] = 1;
	for(int i = 1; i < MAXM; i++) {
		fac[i] = fac[i - 1] * i % MOD;
		inv[i] = qpow(fac[i], MOD - 2);
	}
	for(int i = 1; i < MAXN; i++) {
		if(rd[i - 1] & 1) rd[i] = rd[i - 1] / 2 + 1;
		else rd[i] = rd[i - 1] / 2;
	}
	for(int i = 0; i < K; i++) {
		scanf("%d%d", &p[i].x, &p[i].y);
		if(p[i].x == 1 && p[i].y == 1) has11 = 1;
		if(p[i].x == N && p[i].y == M) hasnm = 1;
	}
	if(!has11) p[K++] = Point(1, 1);
	if(!hasnm) p[K++] = Point(N, M);
	sort(p, p + K, cmp);
	dp[K - 1][0] = 1;
	for(int i = K - 2; i >= 0; i--) {
		for(int j = 0; j <= 22; j++) {
			dp[i][j] = path(p[i].x, p[i].y, N, M);
			for(int k = i + 1; k < K; k++) {
				if(p[k].y < p[i].y) continue;
				ma(dp[i][j], -path(p[i].x, p[i].y, p[k].x, p[k].y)
						* dp[k][j] % MOD);
			}
			for(int k = 0; k < j; k++) ma(dp[i][j], -dp[i][k]);
		}
	}
	long long ans = 0;
	for(int i = 0; i <= 22; i++) {
		if(has11) ma(ans, dp[0][i] * rd[i + hasnm] % MOD);
		else if(i - 1 + hasnm >= 0) ma(ans, dp[0][i] * rd[i - 1 + hasnm] % MOD);
	}
	for(int i = 1; i < K; i++) {
		ma(ans, dp[i][22] * path(1, 1, p[i].x, p[i].y) % MOD);
	}
	/*for(int i = 0; i < K; i++) {
		for(int j = 0; j < 7; j++) {
			printf("%lld ", dp[i][j]);
		}
		puts("");
	}*/
	ans = ans * qpow(path(1, 1, N, M), MOD - 2) % MOD;
	std::cout << ans << std::endl;
	return 0;
}
