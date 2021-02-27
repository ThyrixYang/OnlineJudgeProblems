#include <bits/stdc++.h>

const int MAXE = 1e6 + 300;
const int MAXN = 5e5 + 300;
const long long MOD = 1e9 + 7;
long long qpow(long long a, long long p) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
long long fac[MAXN], inv[MAXN], p2[MAXN];
long long C(int n, int k) {
	if(n < k) return 0;
	return fac[n] * inv[k] % MOD * inv[n - k] % MOD;
}
int a[MAXN][61];
long long c1[61];
int Gauss(int n) {
	int r = 0, c = 0;
	for(; c < 61; c++) {
		for(int i = r; i < n; i++) {
			if(a[i][c] == 1) {
				for(int j = 0; j < 61; j++) {
					std::swap(a[r][j], a[i][j]);
				}
				break;
			}
		}
		if(a[r][c] == 0) continue;
		for(int i = 0; i < n; i++) {
			if(i != r && a[i][c] == 1) {
				for(int j = 0; j < 61; j++) {
					a[i][j] ^= a[r][j];
				}
			}
		}
		r++;
	}
	std::memset(c1, 0, sizeof c1);
	for(int i = 0; i < 61; i++) {
		for(int j = 0; j < r; j++) {
			if(a[j][i] == 1) c1[i] = 1;
		}
	}
	return r;
}
struct edge {
	int from, to, next;
	long long w;
}E[MAXE];
int head[MAXN], eh;
void addEdge(int from, int to, long long w) {
	E[eh].from = from, E[eh].to = to, E[eh].w = w;
	E[eh].next = head[from];
	head[from] = eh++;
}
long long cnt[2][61];
int vis[MAXN];
long long val[MAXN];
int cntVar, cntVex;
void dfs(int v, long long x) {
	val[v] = x;
	vis[v] = 1;
	cntVex++;
	long long tmp = x;
	for(int i = 0; i < 61; i++) {
		cnt[tmp & 1][i]++;
		tmp >>= 1;
	}
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		long long w = E[i].w;
		if(!vis[u]) {
			dfs(u, x ^ w);
		} else {
			long long tmp = (w ^ val[v] ^ val[u]);
			for(int j = 0; j < 61; j++) {
				a[cntVar][j] = (tmp & 1);
				tmp >>= 1;
			}
			cntVar++;
		}
	}
}
long long calc(int s) {
	std::memset(cnt, 0, sizeof cnt);
	cntVex = cntVar = 0;
	dfs(s, 0);
	int R = Gauss(cntVar);
	long long res = 0;
	for(int i = 0; i < 61; i++) {
		long long e[2];
		long long k[2];
		k[0] = k[1] = 0;
		if(c1[i]) {
			e[0] = e[1] = p2[R - 1];
		} else {
			e[0] = p2[R];
			e[1] = 0;
		}
		k[1] = cnt[1][i] * cnt[0][i];
		k[0] = C(cnt[1][i], 2) + C(cnt[0][i], 2);
		k[0] %= MOD;
		long long tmp = k[1] * e[0] % MOD + k[0] * e[1] % MOD;
		tmp %= MOD;
		res = (res + tmp * p2[i] % MOD) % MOD;
	}
	return res;
}
int N, M;
int main() {
	freopen("in", "r", stdin);
	p2[0] = fac[0] = inv[0] = 1;
	for(int i = 1; i < MAXN; i++) {
		fac[i] = fac[i - 1] * i % MOD;
		inv[i] = qpow(fac[i], MOD - 2);
		p2[i] = p2[i - 1] * 2 % MOD;
	}
	std::memset(head, -1, sizeof head);
	std::cin >> N >> M;
	for(int i = 0; i < M; i++) {
		long long x, y, z;
		scanf("%lld%lld%lld", &x, &y, &z);
		addEdge(x, y, z);
		addEdge(y, x, z);
	}
	long long ans = 0;
	for(int i = 1; i <= N; i++) {
		if(!vis[i]) {
			ans = (ans + calc(i)) % MOD;
		}
	}
	std::cout << ans << std::endl;
	return 0;
}