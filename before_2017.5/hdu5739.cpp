#include <bits/stdc++.h>

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
long long inv(long long x) {
	return qpow(x, MOD - 2);
}
const int MAXN = 4e5 + 300;
const int MAXM = 1e6 + 300;
int T;
int n, m;
long long w[MAXN];
struct edge{
	int to, next;
}E[MAXM];
int head[MAXN], eh;
void addEdge(int from, int to) {
	E[eh].to = to, E[eh].next = head[from];
	head[from] = eh++;
}
int fa[MAXN], cnt[MAXN];
long long pw[MAXN];
int find(int x) {
	if(x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
std::vector<int> tmp;
std::vector<int> G[MAXN];
int dfn[MAXN], low[MAXN];
int isCut[MAXN];
int tt = 0;
int stk[MAXN], top;
int sz;
void dfs1(int v, int f = -1) {
	dfn[v] = low[v] = ++tt;
	tmp.push_back(v);
	stk[top++] = v;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(u == f) continue;
		if(dfn[u]) low[v] = std::min(low[v], dfn[u]);
		else {
			dfs1(u, v);
			low[v] = std::min(low[u], low[v]);
			if(low[u] >= dfn[v]) {
				while(stk[--top] != u) {
					G[sz].push_back(stk[top]);
					G[stk[top]].push_back(sz);
				}
				G[sz].push_back(v);
				G[v].push_back(sz);
				G[u].push_back(sz);
				G[sz].push_back(u);
				w[sz] = 1;
				sz++;
			}
		}
	}
}
long long down[MAXN], sum[MAXN];
void dfs3(int v, int f = -1) {
	down[v] = w[v];
	sum[v] = 0;
	for(int i = 0; i < G[v].size(); i++) {
		int u = G[v][i];
		if(u == f) continue;
		dfs3(u, v);
		sum[v] += down[u];
		sum[v] %= MOD;
		down[v] *= down[u];
		down[v] %= MOD;
	}
}
long long res[MAXN];
void dfs4(int v, int f = -1, long long val = 1) {
	//printf("val  %d %lld %lld\n", v, val, down[v]);
	if(f == -1) res[v] = sum[v];
	else res[v] = (val + sum[v]) % MOD;
	long long p = w[v];
	for(int i = 0; i < G[v].size(); i++) {
		int u = G[v][i];
		if(u == f) continue;
		p *= down[u];
		p %= MOD;
	}
	for(int i = 0; i < G[v].size(); i++) {
		int u = G[v][i];
		if(u == f) continue;
		dfs4(u, v, val * p % MOD * inv(down[u]) % MOD);
	}
}
void solve(int s) {
	tmp.clear();
	dfs1(s);
	dfs3(s);
	dfs4(s);
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		scanf("%d%d", &n, &m);

		sz = n + 1;
		memset(head, -1, sizeof (int) * (n + 3) * 2);
		memset(dfn, 0, sizeof (int) * (n + 3) * 2);
		memset(isCut, 0, sizeof (int) * (n + 3) * 2);
		for(int i = 1; i <= n * 2 + 30; i++) G[i].clear();
		eh = 0;

		long long tol = 0;
		for(int i = 1; i <= n; i++) scanf("%lld", &w[i]), fa[i] = i, cnt[i] = 1, pw[i] = w[i], tol += w[i];
		tol %= MOD;
		for(int i = 0; i < m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			addEdge(x, y);
			addEdge(y, x);
			if(find(x) == find(y)) continue;
			tol -= pw[find(x)] + pw[find(y)];
			cnt[find(x)] += cnt[find(y)];
			pw[find(x)] = pw[find(x)] * pw[find(y)] % MOD;
			tol += pw[find(x)];
			tol = (tol % MOD + MOD) % MOD;
			fa[find(y)] = find(x);
		}
		for(int i = 1; i <= n; i++) {
			if(!dfn[i]) solve(i);
		}
		long long out = 0;
		for(int i = 1; i <= n; i++) {
			if(cnt[find(i)] == 1) res[i] = 0;
			long long ans = tol - pw[find(i)];
			ans += res[i];
			ans = (ans % MOD + MOD) % MOD;
			out += ans * i % MOD;
			out %= MOD;
		}
		printf("%lld\n", out);
	}
	return 0;
}
