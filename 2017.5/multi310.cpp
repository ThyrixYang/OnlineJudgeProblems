#include <bits/stdc++.h>

const int MAXN = 1e5 + 3000;
const int MAXM = MAXN * 2;
struct edge {
	int to, next;
}E[MAXM];
int eh = 0;
int head[MAXN];
void addEdge(int from, int to) {
	E[eh].to = to, E[eh].next = head[from];
	head[from] = eh++;
}
int T, n;
int sz[MAXN];
void dfs(int v, int f = -1) {
	int g = 1;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(u == f) continue;
		dfs(u, v);
		g = 0;
	}
	sz[v] = g;
}
int ans;
void dfs2(int v, int f = -1) {
	int g = 0;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(u == f) continue;
		dfs2(u, v);
		g += sz[u];
	}
	if(v != 1){
	if(g % 2) {
		ans++;
		sz[v] = 1;
	} else {
		sz[v] = 2;
		ans += 2;
	}
	}
}
int main() {
	std::cin >> T;
	while(T--) {
		scanf("%d", &n);
		std::memset(head, -1, sizeof (int) * (n + 3));
		for(int i = 0; i < n - 1; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			addEdge(x, y);
			addEdge(y, x);
		}
		ans = 0;
		dfs(1);
		dfs2(1);
		printf("%d\n", ans);
	}
	return 0;
}
