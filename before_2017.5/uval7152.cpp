#include <bits/stdc++.h>

const int MAXV = 1005;
const int MAXE = 1e6;
struct edge {
	int to, cap, cost, next, from;
}E[MAXE];
int head[MAXV], eh;
void addEdge(int from, int to, int cap, int cost) {
	E[eh].to = to, E[eh].cap = cap, E[eh].cost = cost, E[eh].next = head[from];
	E[eh].from = from;
	head[from] = eh++;
	E[eh].to = from, E[eh].cap = 0, E[eh].cost = -cost, E[eh].next = head[to];
	E[eh].from = to;
	head[to] = eh++;
}
bool inq[MAXV];
long long dis[MAXV];
long long vis[MAXV], tmm;
int Q[MAXE], front, back;
int pree[MAXV], prev[MAXV];
long long cost_flow(int s, int t) {
	long long res = 0;
	for(;;) {
		tmm++;
		front = back = 0;
		Q[back++] = s;
		vis[s] = tmm;
		inq[s] = 1;
		dis[s] = 0;
		while(front < back) {
			int v = Q[front++];
			inq[v] = 0;
			for(int i = head[v]; i != -1; i = E[i].next) {
				edge &e = E[i];
				if(e.cap <= 0) continue;
				if(vis[e.to] != tmm || dis[e.to] > dis[v] + e.cost) {
					dis[e.to] = dis[v] + e.cost;
					vis[e.to] = tmm;
					pree[e.to] = i;
					prev[e.to] = v;
					if(!inq[e.to]) inq[e.to] = 1, Q[back++] = e.to;
				}
			}
		}
		if(vis[t] != tmm) {
			return res;
		}
		int d = 1e9;
		for(int v = t; v != s; v = prev[v]) {
			d = std::min(d, E[pree[v]].cap);
		}
		res += d * dis[t];
		for(int v = t; v != s; v = prev[v]) {
			E[pree[v]].cap -= d;
			E[pree[v] ^ 1].cap += d;
		}
	}
	return res;
}
void init() {
	std::memset(head, -1, sizeof head);
	eh = 0;
}
int n, k;
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d%d", &n, &k) != EOF) {
		init();
		int s = n * 2 + 3, t = s + 1;
		for(int i = 1; i <= n; i++) {
			int x;
			scanf("%d", &x);
			addEdge(0, i, 1, x);
		}
		for(int i = 1; i < n; i++) {
			for(int j = i + 1; j <= n; j++) {
				int x;
				scanf("%d", &x);
				addEdge(i + n, j, 1, x);
			}
		}
		addEdge(s, 0, k, 0);
		for(int i = 1; i <= n; i++) {
			addEdge(i, t, 1, 0);
			addEdge(s, i + n, 1, 0);
		}
		long long ans = cost_flow(s, t);
		std::cout << ans << std::endl;
	}
	return 0;
}
