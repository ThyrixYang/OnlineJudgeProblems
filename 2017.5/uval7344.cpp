#include <bits/stdc++.h>

const long long MOD = 1e9 + 7;
int T, N;
int bs[20];
long long dp[1 << 10];
inline ma(long long &a, long long b) {
	a += b;
	if(a >= MOD) a -= MOD;
}
int A[20], ah;
long long p[20][20];
void init() {
	for(int i = 1; i <= 10; i++) {
		p[i][0] = 1;
		for(int j = 1; j < 10; j++) {
			p[i][j] = p[i][j - 1] * i % MOD;
		}
	}
}
long long DP(int p = 0, int up = 1, int one = 1) {
	if(p == 10) return !one;
	long long ans = 0;
	for(int i = 0; i < ah; i++) {
		int d = A[i];

	}
}
void getDP(int mask) {
	ah = 0;
	for(int i = 0; i < 10; i++)
		if(1 & (mask >> i)) A[ah++] = i;
	dp[mask] = DP();
}
void cal(int x) {
	for(int i = 0; i < 10; i++) {
		bs[i] = x % 10;
		x /= 10;
	}
	std::reverse(bs, bs + 10);
}

int main() {
	freopen("./in", "r", stdin);
	init();
	std::cin >> T;
	while(T--) {
		scanf("%d", &N);
		cal(N);
	}
	return 0;
}
