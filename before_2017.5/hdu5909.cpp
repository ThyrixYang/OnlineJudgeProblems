#include <bits/stdc++.h>

const int MAXN = 1026;
const int MAXE = MAXN * 2;
const long long MOD = 1e9 + 7;
struct edge {
	int to, next;
}E[MAXE];
int head[MAXN], eh;
void addEdge(int from, int to) {
	E[eh].to = to, E[eh].next = head[from];
	head[from] = eh++;
}
long long dp[MAXN][MAXN];
long long qpow(long long a, long long p) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
void FWT(long long *f, int n, int on) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < (1 << n); j++) {
			if(j & (1 << i)) continue;
			long long l = f[j], r = f[j | (1 << i)];
			f[j] = (l + r) % MOD, f[j | (1 << i)] = (l - r + MOD) % MOD;
		}
	}
	if(on == -1) {
		long long inv = qpow(1 << n, MOD - 2);
		for(int i = 0; i < (1 << n); i++) {
			f[i] = f[i] * inv % MOD;
		}
	}
}
int T, N, M, K;
void fmulti(long long *a, long long *b, int K) {
	FWT(a, K, 1);
	FWT(b, K, 1);
	for(int i = 0; i < (1 << K); i++) {
		a[i] = a[i] * b[i] % MOD;
	}
	FWT(a, K, -1);
	FWT(b, K, -1);
}
int val[MAXN];
void dfs(int v, int f = -1) {
	std::memset(dp[v], 0, sizeof(long long) * M);
	dp[v][val[v]] = 1;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(u == f) continue;
		dfs(u, v);
		fmulti(dp[v], dp[u], K);
	}
	dp[v][0]++;
	if(dp[v][0] == MOD) dp[v][0] = 0;
}
int main() {
	freopen("in.txt", "r", stdin);
	std::cin >> T;
	while(T--) {
		scanf("%d%d", &N, &M);
		for(int i = 1; i <= N; i++) {
			scanf("%d", &val[i]);
		}
		std::memset(head, -1, sizeof(int) * (N + 3));
		eh = 0;
		for(int i = 0; i < N - 1; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			addEdge(x, y);
			addEdge(y, x);
		}
		K = 0;
		while((1 << K) != M) K++;
		dfs(1);
		for(int i = 2; i <= N; i++) {
			for(int j = 0; j < M; j++) {
				dp[1][j] += dp[i][j];
				if(dp[1][j] >= MOD) dp[1][j] -= MOD;
			}
		}
		dp[1][0] -= N - MOD;
		dp[1][0] %= MOD;
		for(int i = 0; i < M; i++) {
			printf("%lld", dp[1][i]);
			if(i < M - 1) printf(" ");
		}
		puts("");
	}
	return 0;
}
