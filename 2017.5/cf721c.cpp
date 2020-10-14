#include <bits/stdc++.h>

typedef std::pair<long long, long long> P;
const int MAXE = 5e6;
const int MAXN = 5005;
struct edge {
	int to, w, next;
}E[MAXE];
int head[MAXN], eh;
int N, M, T;
void addEdge(int from, int to, int w) {
	E[eh].to = to, E[eh].w = w, E[eh].next = head[from];
	head[from] = eh++;
}
int dis[MAXN * MAXN];
int fore[MAXN * MAXN];
int se[MAXN], sh;
int main() {
	freopen("./in", "r", stdin);
	std::memset(head, -1, sizeof head);
	std::cin >> N >> M >> T;
	for(int i = 0; i < M; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		x--, y--;
		addEdge(x, y, z);
	}
	std::memset(dis, 0x3f, sizeof dis);
	dis[0] = 0;
	std::priority_queue<P, std::vector<P>, std::greater<P> > Q;
	Q.push(P(0, 0));
	while(!Q.empty()) {
		long long d = Q.top().first;
		int v = Q.top().second;
		Q.pop();
		if(dis[v] < d) continue;
		int pos = v / N, step = v % N;
		for(int i = head[pos]; i != -1; i = E[i].next) {
			int to = E[i].to;
			int tid = to * N + step + 1;
			if(dis[to * N + step + 1] > dis[v] + E[i].w) {
				dis[to * N + step + 1] = dis[v] + E[i].w;
				Q.push(P(dis[to * N + step + 1], to * N + step + 1));
				fore[tid] = v;
			}
		}
	}
	int maxlen = 0;
	for(int i = 0; i < N; i++) {
		if(dis[(N - 1) * N + i] <= T) {
			maxlen = i;
		}
	}
	printf("%d\n", maxlen + 1);
	int v = (N - 1) * N + maxlen;
	while(v != 0) {
		se[sh++] = v / N;
		v = fore[v];
	}
	se[sh++] = 0;
	std::reverse(se, se + sh);
	for(int i = 0; i < sh; i++) {
		printf("%d ", se[i] + 1);
	}
	return 0;
}
