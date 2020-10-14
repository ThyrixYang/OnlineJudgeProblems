#include <bits/stdc++.h>

const int MAXN = 1e5 + 300;
std::vector<int> G[MAXN];
int N, M, K;
int ind[MAXN];
std::priority_queue<int> qmax, qmin;
typedef std::pair<int, int> P;
std::vector<P> op;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N >> M >> K;
	for(int i = 0; i < M; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
		ind[y]++;
	}
	for(int i = 1; i <= N; i++) {
		if(ind[i] == 0) qmin.push(-i);
	}
	int last = 0;
	for(int i = 0; i < N; i++) {
		while(K > 0 && !qmin.empty()) {
			if(!qmax.empty() && -qmin.top() > qmax.top() && qmin.size() == 1) break;
			if(qmax.empty() && qmin.size() == 1) break;
			K--;
			qmax.push(-qmin.top());
			qmin.pop();
		}
		int v;
		if(qmin.size()) {
			v = -qmin.top();
			qmin.pop();
		} else {
			v = qmax.top();
			qmax.pop();
			if(last) op.push_back(P(last, v));
		}
		printf("%d ", v);
		for(auto u: G[v]) {
			if(--ind[u] == 0) qmin.push(-u);
		}
		last = v;
	}
	puts("");
	std::cout << op.size() << std::endl;
	for(auto x: op) {
		printf("%d %d\n", x.first, x.second);
	}
	return 0;
}
