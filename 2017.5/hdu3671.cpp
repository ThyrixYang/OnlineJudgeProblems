#include <bits/stdc++.h>

const int MAXM = 2e4 + 3000;
struct Node {
	int to, next;
}E[MAXM];
const int MAXN = 1005;
int head[MAXN], eh;
void addEdge(int from, int to) {
	E[eh].to = to, E[eh].next = head[from];
	head[from] = eh++;
}
int ans;
int n, m;
int fa[MAXN];
int cnt[MAXN];
int del;
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
int tm;
int dfn[MAXN], low[MAXN];
int cut;
void dfs(int v, int f = -1) {
	dfn[v] = low[v] = ++tm;
	int g = 0;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(u == f || u == del) continue;
		if(dfn[u]) low[v] = std::min(low[v], dfn[u]);
		else {
			dfs(u, v);
			low[v] = std::min(low[v], low[u]);
			g += low[u] >= dfn[v];
		}
	}
	if(f == -1 && g >= 2) cut++;
	if(f != -1 && g >= 1) cut++;
}
void cal() {
	int c = n - 1;
	int c1 = n - 1;
	for(int i = 1; i <= n; i++) fa[i] = i, cnt[i] = 1;
	for(int i = 1; i <= n; i++) {
		if(i == del) continue;
		for(int j = head[i]; j != -1; j = E[j].next) {
			int v = E[j].to;
			if(v == del) continue;
			if(find(v) == find(i)) continue;
			if(cnt[find(v)] == 1) c1--;
			if(cnt[find(i)] == 1) c1--;
			cnt[find(v)] += cnt[find(i)];
			fa[find(i)] = find(v);
			c--;
		}
	}
	if(c >= 3) ans += n - 1;
	else if(c == 2) {
		if(c1 && n > 3) ans += n - 2;
		else if(!c1) ans += n - 1;
	}else {
		std::memset(dfn, 0, sizeof (int) * (n + 3));
		cut = 0;
		if(del == 1) dfs(2);
		else dfs(1);
		ans += cut;
	}
}
int cas = 0;
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d%d", &n, &m)) {
		if(n == 0 && m == 0) break;
		memset(head, -1, sizeof (int) * (n + 3));
		eh = 0;
		for(int i = 0; i < m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			addEdge(x, y);
			addEdge(y, x);
		}
		ans = 0;
		for(int i = 1; i <= n; i++) {
			del = i;
			cal();
		}
		ans >>= 1;
		printf("Case %d: %d\n", ++cas, ans);
	}
	return 0;
}
