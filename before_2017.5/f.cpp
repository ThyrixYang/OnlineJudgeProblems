#include <bits/stdc++.h>

const int MAXM = 2e6;
const int MAXN = 1e5 + 3000;
struct edge {
	int to, next;
}E[MAXM];
int head[MAXN];
int eh;
void addEdge(int from, int to) {
	E[eh].to = to, E[eh].next = head[from];
	head[from] = eh++;
}
int T, n, m;
int vis[MAXN][2];
int col[MAXN];
int tm;
int pre[MAXN];
int st, ed;
int in[MAXN];
int found;
void dfs(int v, int c = 0) {
	if(found) return;
	vis[v][c] = tm;
	col[v] = c;
	in[v] = 1;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(in[u]) {
			if(col[u] == col[v]) {
				st = v;
				ed = u;
				found = 1;
				break;
			}
		} else {
			if(vis[u][c ^ 1] != tm) dfs(u, c ^ 1), pre[u] = v;
			if(found) break;
		}
	}
	in[v] = 0;
}
void init() {
	eh = 0;
	std::memset(head, -1, sizeof(int) * (n + 33));
	tm++;
	found = 0;
}
int A[MAXN], ah;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		scanf("%d%d", &n, &m);
		init();
		for(int i = 0; i < m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			addEdge(x, y);
		}
		for(int i = 1; i <= n; i++) if(vis[i][0] != tm) {
			dfs(i);
		}
		if(found) {
			puts("1");
			ah = 0;
			int v = st;
			while(v != ed) {
				A[ah++] = v;
				v = pre[v];
			}
			A[ah++] = v;
			std::reverse(A, A + ah);
			printf("%d\n", ah);
			for(int i = 0; i < ah; i++) printf("%d\n", A[i]);
		} else {
			puts("-1");
		}
	}
	return 0;
}
