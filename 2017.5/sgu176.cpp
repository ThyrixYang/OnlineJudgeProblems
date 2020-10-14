#include <bits/stdc++.h>

const int MAXN = 105;
const int MAXE = 1e4;
struct edge {
	 int to, cap, next;
}E[MAXE];
int head[MAXN], eh;
void addEdge(int from, int to, int cap) {
	E[eh].to = to, E[eh].cap = cap, E[eh].next = head[from];
	head[from] = eh++;
	E[eh].to = from, E[eh].cap = 0, E[eh].next = head[to];
	head[to] = eh++;
}
int vis[MAXN], tmm;
int que[MAXE], front, back;
int dis[MAXN];
int bfs(int s, int t) {
	tmm++;
	front = back = 0;
	que[back++] = s;
	dis[s] = 0;
	vis[s] = tmm;
	while(front < back) {
		int v = que[front++];
		for(int i = head[v]; i != -1; i = E[i].next) {
			int u = E[i].to;
			if(!E[i].cap) continue;
			if(vis[u] != tmm) {
				vis[u] = tmm;
				dis[u] = dis[v] + 1;
				que[back++] = u;
			}
		}
	}
	return vis[t] == tmm;
}
int iter[MAXN];
int dfs(int v, int t, int f) {
	if(v == t) return f;
	int c = 0;
	for(int &i = iter[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(!E[i].cap || dis[u] <= dis[v]) continue;
		int d = dfs(u, t, std::min(f - c, E[i].cap));
		c += d;
		E[i].cap -= d;
		E[i ^ 1].cap += d;
		if(c == f) return f;
	}
	return c;
}
int dinic(int s, int t) {
	int flow = 0;
	for(;;) {
		if(!bfs(s, t)) return flow;
		for(int i = 0; i < MAXN; i++) iter[i] = head[i];
		int d;
		while((d = dfs(s, t, 1e9)) != 0) flow += d;
	}
	return flow;
}
void clearGraph() {
	eh = 0;
	std::memset(head, -1, sizeof head);
}
int N, M;
int ins[MAXN];
int ide[MAXE];
int Cap[MAXE];
int main() {
	freopen("./in", "r", stdin);
	clearGraph();
	std::cin >> N >> M;
	int ss = N + 2, tt = ss + 1;
	for(int i = 0; i < M; i++) {
		int u, v, z, c;
		scanf("%d%d%d%d", &u, &v, &z, &c);
		if(c == 0) {
			addEdge(u, v, z);
			ide[i] = eh - 1;
		} else {
			ide[i] = -1;
			Cap[i] = z;
			ins[v] += z;
			ins[u] -= z;
		}
	}
	int sum = 0;
	for(int i = 1; i <= N; i++) {
		if(ins[i] > 0) {
			addEdge(ss, i, ins[i]);
			sum += ins[i];
		} else if(ins[i] < 0) {
			addEdge(i, tt, -ins[i]);
		}
	}
	int res = dinic(ss, tt);
	addEdge(N, 1, 1e9);
	res += dinic(ss, tt);
	if(res != sum) {
		puts("Impossible");
	} else {
		printf("%d\n", E[eh - 1].cap);
		for(int i = 0; i < M; i++) {
			if(ide[i] >= 0) printf("%d ", E[ide[i]].cap);
			else printf("%d ", Cap[i]);
		}
	}
	return 0;
}
