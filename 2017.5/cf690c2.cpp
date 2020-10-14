#include <bits/stdc++.h>

const int MAXN = 1e6;
std::vector<int> G[MAXN];
int n, m;
int dis[MAXN];
int vis[MAXN];
void dfs(int v, int d = 0) {
	vis[v] = 1;
	dis[v] = d;
	for(int i = 0; i < G[v].size(); i++) {
		int u = G[v][i];
		if(vis[u]) continue;
		dfs(u, d + 1);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n - 1; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	memset(dis, 0x3f, sizeof dis);
	memset(vis, 0, sizeof vis);
	dfs(1);
	int Max = 0, v = 0;
	for(int i = 1; i <= n; i++) {
		if(dis[i] > Max) {
			Max = dis[i];
			v = i;
		}
	}
	memset(vis, 0, sizeof vis);
	dfs(v);
	for(int i = 1; i <= n; i++) {
		Max = std::max(Max, dis[i]);
	}
	std::cout << Max;
	return 0;
}
