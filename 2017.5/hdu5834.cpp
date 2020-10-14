#include <bits/stdc++.h>

const int MAXN = 1e5 + 300;
const int MAXE = MAXN * 2;
struct edge {
	int to, w, next;
}E[MAXE];
int T;
int n;
int val[MAXN];
int head[MAXN];
int eh;
int cas;
void addEdge(int from, int to, int w) {
	E[eh].to = to, E[eh].w = w, E[eh].next = head[from];
	head[from] = eh++;
}
int back[MAXN], go[MAXN];
int son[MAXN];
void dfs1(int v = 1, int f = 0) {
	back[v] = val[v];
	go[v] = val[v];
	son[v] = -1;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		int w = E[i].w;
		if(u == f) continue;
		dfs1(u, v);
		int t1 = std::max(0, back[u] - 2 * w);
		int t2 = std::max(0, go[u] - w);
		if(back[v] + t2 > go[v] + t1) {
			son[v] = u;
			go[v] = back[v] + t2;
		} else go[v] += t1;
		back[v] += t1;
	}	
}
int ans[MAXN];
void dfs2(int v = 1, int f = 0, int sback = 0, int sgo = 0) {
	sback = std::max(sback, 0);
	sgo = std::max(sgo, 0);
	ans[v] = std::max(sback + go[v], sgo + back[v]);
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		int w = E[i].w;
		if(u == f) continue;
		if(u == son[v]) {
			int s1 = val[v], s2 = val[v];
			for(int i = head[v]; i != -1; i = E[i].next) {
				int u = E[i].to;
				int w = E[i].w;
				if(u == son[v] || u == f) continue;
				int t1 = std::max(0, back[u] - w * 2);
				int t2 = std::max(0, go[u] - w);
				if(s1 + t2 > s2 + t1) {
					s2 = s1 + t2;
				} else s2 += t1;
				s1 += t1;
			}
			dfs2(u, v, sback + s1 - w * 2, 
					std::max(sback + s2 - w, sgo + s1 - w));
		} else {
			int t = std::max(0, back[u] - 2 * w);
			dfs2(u, v, sback + back[v] - t - w * 2, 
					std::max(sback + go[v] - t - w, sgo + back[v] - t - w));
		}
	}
}
int main() {

	freopen("./in", "r", stdin);

	std::cin >> T;
	while(T--) {
		printf("Case #%d:\n", ++cas);
		scanf("%d", &n);
		std::memset(head, -1, sizeof (int) * (n + 3));
		eh = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &val[i]);
		for(int i = 0; i < n - 1; i++) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			addEdge(x, y, z);
			addEdge(y, x, z);
		}
		dfs1();
		dfs2();
		for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	}

	return 0;

}
