#include <bits/stdc++.h>

const int maxn = 2e6;
struct Edge{
	int to,w;
	Edge(int to, int w):to(to), w(w) {}
};
std::vector<Edge> G[maxn];
int dis[maxn];
int dij(int s, int t) {
	memset(dis, 0x3f, sizeof dis);
	dis[s] = 0;
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > Q;
	Q.push(std::make_pair(0, s));
	while(!Q.empty()) {
		int v = Q.top().second;
		int d = Q.top().first;
		Q.pop();
		if(d > dis[v]) continue;
		for(int i = 0; i < G[v].size(); i++ ) {
			int to = G[v][i].to;
			int w = G[v][i].w;
			if(dis[to] > dis[v] + w){
				dis[to] = dis[v] + w;
				Q.push(std::make_pair(dis[to], to));
			}
		}
	}
	return dis[t];
}
void addEdge(int from, int to, int w) {
	G[from].push_back(Edge(to, w));
	G[to].push_back(Edge(from, w));
}
int n, m, x;
int main() {
	std::cin >> n >> m;
	int s = (n - 1) * (m - 1) * 2;
	int t = s + 1;
	for(int i = 0; i < m - 1; i++) {
		scanf("%d", &x);
		addEdge(i, s, x);
	}
	for(int i = 1; i < n - 1; i++) {
		for(int j = 0; j < m - 1; j++) {
			scanf("%d", &x);
			int y = i * (m - 1) * 2 + j;
			addEdge(y, y - m + 1, x);
		}
	}
	for(int i = 0; i < m - 1; i++) {
		int y = (n - 1) * (m - 1) * 2 - m + 1;
		scanf("%d", &x);
		addEdge(y + i, t, x);
	}
	for(int i = 0; i < n - 1; i++) {
		int y = i * (m - 1) * 2;
		for(int j = 0; j < m; j++) {
			scanf("%d", &x);
			if(j == 0) addEdge(t, y + m - 1, x);
			else if(j == m - 1) addEdge(s, y + m - 2, x);
			else addEdge(y + j - 1, y + j - 1 + m, x);
		}
	}
	for(int i = 0; i < n - 1; i++) {
		for(int j = 0; j < m - 1; j++) {
			scanf("%d", &x);
			int y = i * (m - 1) * 2;
			addEdge(y + j, y + m - 1 + j, x);
		}
	}
	std::cout << dij(s, t) << std::endl;
	return 0;
}
