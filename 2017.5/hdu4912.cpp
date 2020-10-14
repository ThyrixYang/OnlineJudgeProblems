#include <bits/stdc++.h>


const int MAXN = 3e5;
struct edge {
	int to, next;
}E[MAXN];
int eh;
int head[MAXN];
int fa[20][MAXN];
int dep[MAXN];
int used[MAXN];
void mark(int v, int f) {
	if(used[v]) return;
	used[v] = 1;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(u == f) continue;
		mark(u, v);
	}
}
void dfs(int v, int f = 0, int d = 0) {
	fa[0][v] = f;
	dep[v] = d;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(u != f) dfs(u, v, d + 1);
	}
}
int n, m;
void init_lca() {
	for(int k = 1; k < 20; k++) {
		for(int i = 1; i <= n; i++) {
			fa[k][i] = fa[k - 1][fa[k - 1][i]];
		}
	}
}
int lca(int a, int b) {
	if(dep[a] < dep[b]) std::swap(a, b);
	for(int k = 19; k >= 0; k--) {
		if(dep[a] - dep[b] >= (1 << k)) a = fa[k][a];
	}
	if(a == b) return a;
	for(int k = 19; k >= 0; k--) {
		if(fa[k][a] != fa[k][b]) a = fa[k][a], b = fa[k][b];
	}
	return fa[0][a];
}
void addEdge(int from, int to) {
	E[eh].to = to, E[eh].next = head[from];
	head[from] = eh++;
}
void clear(int n) {
	memset(head, -1, sizeof (int) * (n + 3));
	memset(used, 0, sizeof (int) * (n + 3));
	eh = 0;
}
struct Node {
	int u, v, x;
	bool operator < (const Node &C) const {
		return dep[x] > dep[C.x];
	}
}N[MAXN];
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d%d", &n, &m) != EOF) {
		clear(n);
		for(int i = 0; i < n - 1; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			addEdge(x, y);
			addEdge(y, x);
		}
		dfs(1);
		init_lca();
		for(int i = 0; i < m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			int x = lca(u, v);
			N[i].u = u, N[i].v = v, N[i].x = x;
		}
		std::sort(N, N + m);
		int ans = 0;
		for(int i = 0; i < m; i++) {
			if(!used[N[i].v] && !used[N[i].u]) {
				mark(N[i].x, fa[0][N[i].x]);
				ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
