#include <bits/stdc++.h>

const int MAXN = 2e6 + 300;
void FWT(long long *f, int n, int on) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < (1 << n); j++) {
			if(j & (1 << i)) continue;
			long long l = f[j], r = f[j | (1 << i)];
			f[j] = (l + r), f[j | (1 << i)] = (l - r);
		}
	}
	if(on == -1) {
		for(int i = 0; i < (1 << n); i++) {
			f[i] /= (1 << n);
		}
	}
}
char B[20][MAXN];
int N, M;
long long x1[MAXN], x2[MAXN];
int cnt[MAXN];
int main() {
	freopen("in", "r", stdin);
	for(int i = 0; i < MAXN; i++) {
		int x = i;
		while(x > 0) {
			if(x & 1) cnt[i]++;
			x >>= 1;
		}
	}
	std::cin >> N >> M;
	for(int i = 0; i < N; i++) {
		scanf("%s", B[i]);
	}
	for(int i = 0; i < M; i++) {
		long long x = 0;
		for(int j = 0; j < N; j++) {
			x <<= 1;
			x += B[j][i] - '0';
		}
		x1[x]++;
	}
	for(int i = 0; i < (1 << N); i++) {
		x2[i] = std::min(cnt[i], N - cnt[i]);
	}
	FWT(x1, N, 1);
	FWT(x2, N, 1);
	for(int i = 0; i < (1 << N); i++) {
		x1[i] = x1[i] * x2[i];
	}
	FWT(x1, N, -1);
	long long ans = 1e9;
	for(int i = 0; i < (1 << N); i++) {
		ans = std::min(ans, x1[i]);
	}
	std::cout << ans << std::endl;
	return 0;
}