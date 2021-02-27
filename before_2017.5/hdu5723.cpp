#include <bits/stdc++.h>

const int MAXN = 2e5;
const int MAXM = 2e6;
struct Edge{
	int a, b, w;
	Edge(int a = 0, int w = 0):a(a), w(w){}
	bool operator < (const Edge &C)const {
		return w < C.w;
	}
};
int T, n, m;
std::vector<Edge> G[MAXN];
Edge es[MAXM];
int fa[MAXN];
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
int cnt[MAXN];
double len = 0;
void dfs(int v, int f) {
	cnt[v] = 1;
	for(int i = 0; i < G[v].size(); i++) {
		int u = G[v][i].a;
		if(u == f) continue;
		dfs(u, v);
		cnt[v] += cnt[u];
	}
}
void dfs2(int v, int f, long long w) {
	len += (long long)cnt[v] * (n - cnt[v]) * w / ((double)n * (n - 1));
	for(int i = 0; i < G[v].size(); i++) {
		int u = G[v][i].a, w = G[v][i].w;
		if(u == f) continue;
		dfs2(u, v, w);
	}
}
int main() {
	std::cin >> T;
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i <= n; i++) G[i].clear(), fa[i] = i;
		for(int i = 0; i < m; i++) {
			scanf("%d%d%d", &es[i].a, &es[i].b, &es[i].w);
		}
		len = 0;
		long long cost = 0;
		std::sort(es, es + m);
		for(int i = 0; i < m; i++) {
			int a = es[i].a, b = es[i].b, w = es[i].w;
			if(find(a) == find(b)) continue;
			fa[find(a)] = find(b);
			cost += w;
			G[a].push_back(Edge(b, w));
			G[b].push_back(Edge(a, w));
		}
		dfs(1, -1);
		dfs2(1, -1, 0);
		printf("%lld %.2f\n", cost, len * 2);
	}
	return 0;
}
