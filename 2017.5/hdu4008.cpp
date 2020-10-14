#include <bits/stdc++.h>

using namespace std;
const int MAXN = 1e5 + 300;
const int MAXE = MAXN * 2;
const int INF = 1e9;
struct edge {
	int to, next;
}E[MAXE];
int head[MAXN], eh;
void addEdge(int from, int to) {
	E[eh].to = to, E[eh].next = head[from];
	head[from] = eh++;
}
int T;
int N, Q;
int dfn[MAXN][2];
int tx;
int mind[MAXN];
int minv[MAXN], sminv[MAXN];
int fa[20][MAXN];
int dep[MAXN];
void dfs(int v, int f = 0, int d = 0) {
	fa[0][v] = f;
	dfn[v][0] = tx++;
	dep[v] = d;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(u == f) continue;
		dfs(u, v, d + 1);
		sminv[v] = std::min(sminv[v], u);
		if(sminv[v] < minv[v]) swap(sminv[v], minv[v]);
		mind[v] = min(mind[v], min(u, mind[u]));
	}
	dfn[v][1] = tx;
}
void LCA_pre() {
	for(int k = 1; k < 20; k++) {
		for(int i = 1; i <= N; i++) {
			fa[k][i] = fa[k - 1][fa[k - 1][i]];
		}
	}
}
int lca(int a, int b) {
	if(a == b) return a;
	if(dep[a] < dep[b]) std::swap(a, b);
	for(int k = 19; k >= 0; k--) {
		if((dep[a] - dep[b]) & (1 << k)) {
			a = fa[k][a];
		}
	}
	if(a == b) return a;
	for(int k = 19; k >= 0; k--) {
		if(fa[k][a] != fa[k][b]) {
			a = fa[k][a];
			b = fa[k][b];
		}
	}
	return fa[0][a];
}
int getson(int a, int b) {
	for(int k = 19; k >= 0; k--) {
		if((dep[b] - dep[a] - 1) & (1 << k)) {
			b = fa[k][b];
		}
	}
	return b;
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		scanf("%d%d", &N, &Q);
		std::memset(head, -1, sizeof (int) * (N + 3));
		for(int i = 0; i <= N; i++) {
			mind[i] = minv[i] = sminv[i] = INF;
		}
		tx = eh = 0;
		for(int i = 0; i < N - 1; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			addEdge(x, y);
			addEdge(y, x);
		}
		dfs(1);
		LCA_pre();
		int minid = INF, sminid = INF;
		int min2[2], smin2[2];
		min2[0] = smin2[0] = INF;
		for(int i = head[1]; i != -1; i = E[i].next) {
			int v = E[i].to;
			if(v < sminid) sminid = v;
			if(sminid < minid) swap(sminid, minid);
			int d = min(mind[v], v);
			if(d < smin2[0]) smin2[0] = d, smin2[1] = v;
			if(smin2[0] < min2[0]) {
				swap(smin2[0], min2[0]);
				swap(smin2[1], min2[1]);
			}
		}
		while(Q--) {
			int X, Y;
			scanf("%d%d", &X, &Y);
			if(dfn[Y][0] < dfn[X][1] && dfn[Y][0] >= dfn[X][0]) {
				if(minv[Y] == INF) puts("no answers!");
				else printf("%d %d\n", minv[Y], mind[Y]);
			} else {
				int lc  = lca(X, Y);
				if(Y == 1) {
					int s = getson(Y, X);
					int ans1 = minid;
					int ans2 = min2[0];
					if(s == minid) ans1 = sminid;
					if(s == min2[1]) ans2 = smin2[0];
					if(ans2 == INF) puts("no answers!");
					else printf("%d %d\n", ans1, ans2);
				} else if(lc == Y) {
					int s = getson(Y, X);
					int mm = minv[Y];
					if(s == minv[Y]) mm = sminv[Y];
					mm = std::min(fa[0][Y], mm);
					int ms = 1;
					printf("%d %d\n", mm, ms);
				} else {
					if(mind[Y] == INF) {
						puts("no answers!");
					} else {
						printf("%d %d\n", minv[Y], mind[Y]);
					}
				}
			}
		}
		puts("");
	}
	return 0;
}
