#include <bits/stdc++.h>

const long long MOD = 1e9 + 7;
const int MAXN = 60;
int N, M, T, cas = 0;
int mat[MAXN][MAXN];
long long qpow(long long a, long long p) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
int cnt;
int v[MAXN], vh;
void dfs(int p) {
	cnt++;
	for(int i = p; i < N; i++) {
		int f = 1;
		for(int j = 0; j < vh && f; j++) {
			for(int k = j + 1; k < vh && f; k++) {
				int v1 = v[j], v2 = v[k];
				if(mat[i][v1] && mat[i][v2] && mat[v1][v2]) {
					f = 0;
				}
				if(!mat[i][v1] && !mat[i][v2] && !mat[v1][v2]) {
					f = 0;
				}
			}
		}
		if(!f) continue;
		v[vh++] = i;
		dfs(i + 1);
		vh--;
	}
}
int main() {
	freopen("in.txt", "r", stdin);
	std::cin >> T;
	while(T--) {
		printf("Case #%d: ", ++cas);
		scanf("%d%d", &N, &M);
		std::memset(mat, 0, sizeof mat);
		for(int i = 0; i < M; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			x--, y--;
			mat[x][y] = mat[y][x] = 1;
		}
		long long ans = qpow(2, N);
		cnt = 0;
		dfs(0);
		ans = (ans - cnt + MOD) % MOD;
		printf("%lld\n", ans);
	}
	return 0;
}
