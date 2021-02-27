#include <bits/stdc++.h>

const int MAXN = 1e5 + 3000;
std::vector<int> G[MAXN];
int n, m, k;
int ind[MAXN];
std::vector<std::pair<int, int> > op;
std::priority_queue<int> Q;
void addEdge(int from, int to) {
	op.push_back(std::make_pair(from, to));
	G[from].push_back(to);
}
int topo[MAXN], tp;
void gao() {
	std::priority_queue<int> que;
	std::memset(ind, 0, sizeof ind);
	for(int i = 1; i <= n; i++) {
		for(auto &u: G[i]) {
			ind[u]++;
		}
	}
	for(int i = 1; i <= n; i++)
		if(ind[i] == 0) que.push(-i);
	while(!que.empty()) {
		int v = -que.top();
		topo[tp++] = v;
		que.pop();
		for(auto &u: G[v]) {
			if(--ind[u] == 0) que.push(-u);
		}
	}
}
int main() {
	freopen("./in", "r", stdin);
	//freopen("graph.in", "r", stdin);
	//freopen("graph.out", "w", stdout);
	std::cin >> n >> m >> k;
	while(m--) {
		int x, y;
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
		ind[y]++;
	}
	for(int i = 1; i <= n; i++) {
		if(ind[i] == 0) Q.push(i);
	}
	while(!Q.empty()) {
		if(k < (int)Q.size() - 1) {
			std::vector<int> V;
			while(!Q.empty()) {
				V.push_back(Q.top());
				Q.pop();
			}
			std::reverse(V.begin(), V.end());
			int y = k;
			if(k) addEdge(V.back(), V[y - 1]), k--;
			for(int i = 0; i < y - 1; i++)
				if(k) addEdge(V[i + 1] , V[i]), k--;
			break;
		}
		int v = Q.top();
		Q.pop();
		int maxs = 0;
		for(auto &u: G[v])
			maxs = std::max(maxs, u);
		if(!Q.empty()) {
			int tv = Q.top();
			if(tv > maxs) {
				if(--k >= 0)
					addEdge(v, tv);
			} else {

			}
		} else {

		}
		for(auto &u: G[v]) {
			if(--ind[u] == 0) Q.push(u);
		}
	}
	gao();
	for(int i = 0; i < n; i++) printf("%d " ,topo[i]);
	puts("");
	std::cout << op.size() << std::endl;
	for(auto &x: op) {
		printf("%d %d\n", x.first, x.second);
	}
	return 0;
}
