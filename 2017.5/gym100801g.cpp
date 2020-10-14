#include <bits/stdc++.h>

const int MAXN = 2e5;
typedef std::pair<int, int> P;
std::vector<int> G[MAXN];
int n, m, k;
int ind[MAXN];
int que[MAXN], back;
std::priority_queue<int> qmin, qmax;
std::vector<P> op;
void addEdge(int from, int to) {
	op.push_back(P(from, to));
	G[from].push_back(to);
}
void topo() {
	std::memset(ind, 0, sizeof ind);
	for(int v = 1; v <= n; v++) {
		for(auto &u: G[v]) {
			ind[u] ++;
		}
	}
	std::priority_queue<int> Q;
	for(int i = 1; i <= n; i++) {
		if(ind[i] == 0) Q.push(-i);
	}
	while(!Q.empty()) {
		int v = -Q.top();
		printf("%d ", v);
		Q.pop();
		for(auto &u: G[v]) {
			if(--ind[u] == 0) Q.push(-u);
		}
	}
}
int main() {
	freopen("./in", "r", stdin);
	//freopen("graph.in", "r", stdin);
	//freopen("graph.out", "w", stdout);
	std::cin >> n >> m >> k;
	for(int i = 0; i < m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
		ind[y]++;
	}
	for(int i = 1; i <= n; i++) {
		if(ind[i] == 0) qmin.push(-i);
	}
	for(;;) {
		if(qmax.empty()) {
			if(qmin.empty()) break;
			while(!qmin.empty()) {
				qmax.push(-qmin.top());
				qmin.pop();
			}
			int v = qmax.top();
			qmax.pop();
			while(!qmax.empty()) {
				qmin.push(-qmax.top());
				qmax.pop();
			}
			qmax.push(v);
		}
		if(k < (int) qmin.size()) {
			for(int i = 0; i < k; i++) {
				int v = -qmin.top();
				qmin.pop();
				qmax.push(v);
			}
			break;
		} else {
			k -= qmin.size();
			while(!qmin.empty()) {
				qmax.push(-qmin.top());
				qmin.pop();
			}
		}
		if(qmax.empty()) break;
		int v = qmax.top();
		qmax.pop();
		int tm = 0;
		for(auto &u: G[v]) {
			if(--ind[u] == 0) {
				qmin.push(-u);
				tm = std::max(tm, u);
			}
		}
		if(qmax.size()) {
			if(tm < qmax.top()) addEdge(v, qmax.top());
			if(tm >= qmax.top()) k++;
		}
	}
	while(qmax.size() > 1) {
		int v = qmax.top();
		qmax.pop();
		addEdge(v, qmax.top());
	}
	topo();
	puts("");
	std::cout << op.size() << std::endl;
	for(auto &x: op) {
		printf("%d %d\n", x.first, x.second);
	}
	return 0;
}
