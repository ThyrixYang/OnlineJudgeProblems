#include <bits/stdc++.h>

const int MAXE = 1e6;
const int MAXN = 1005;
struct edge {
	int to, next, from;
	long long w;
}E[MAXE];
int head[MAXN], eh;
void addEdge(int from, int to, long long w) {
	E[eh].from = from, E[eh].to = to, E[eh].w = w, E[eh].next = head[from];
	head[from] = eh++;
}
int N, M, L, S, T;
std::vector<int> spe;
long long dis[MAXN];
typedef std::pair<long long, int> P;
#define mp std::make_pair
long long dij() {
	std::memset(dis, 0x3f, sizeof dis);
	dis[S] = 0;
	std::priority_queue<P, std::vector<P>, std::greater<P> > Q;
	Q.push(P(0, S));
	while(!Q.empty()) {
		int v = Q.top().second;
		long long d = Q.top().first;
		Q.pop();
		if(dis[v] < d) continue;
		for(int i = head[v]; i != -1; i = E[i].next) {
			int u = E[i].to;
			long long w = E[i].w;
			if(dis[u] > dis[v] + w) {
				dis[u] = dis[v] + w;
				Q.push(P(dis[u], u));
			}
		}
	}
	return dis[T];
}
int main() {
	freopen("./in", "r", stdin);
	std::memset(head, -1, sizeof head);
	std::cin >> N >> M >> L >> S >> T;
	for(int i = 0; i < M; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		addEdge(x, y, z);
		addEdge(y, x, z);
		if(z == 0) spe.push_back(eh - 2);
	}
	for(auto i: spe) {
		E[i].w = E[i ^ 1].w = 1e10;
	}
	long long maxlen = dij();
	for(auto i: spe) {
		E[i].w = E[i ^ 1].w = 1;
	}
	long long minlen = dij();
	if(L < minlen || L > maxlen) {
		puts("NO");
		return 0;
	}
	int l = -1, r = spe.size();
	while(r - l > 1) {
		int mid = (r + l) >> 1;
		for(int i = 0; i < mid; i++) {
			int id = spe[i];
			E[id].w = E[id ^ 1].w = 1;
		}
		for(int i = mid; i < spe.size(); i++) {
			int id = spe[i];
			E[id].w = E[id ^ 1].w = 1e10;
		}
		long long len = dij();
		if(len <= L) r = mid;
		else l = mid;
	}
	for(int i = 0; i < r; i++) {
		int id = spe[i];
		E[id].w = E[id ^ 1].w = 1;
	}
	for(int i = r; i < spe.size(); i++) {
		int id = spe[i];
		E[id].w = E[id ^ 1].w = 1e10;
	}
	long long dd = dij();
	puts("YES");
	int rr = r;
	if(rr > 0) {
		int fs = spe[rr - 1];
		long long l = 0, r = 1e9 + 7;
		while(r - l > 1) {
			long long mid = (r + l) >> 1;
			E[fs].w = E[fs ^ 1].w = mid;
			long long len = dij();
			if(len >= L) r = mid;
			else l = mid;
		}
		E[fs].w = E[fs ^ 1].w = r;
	}
	for(int i = 0; i < eh; i += 2) {
		printf("%d %d %lld\n", E[i].from, E[i].to, E[i].w);
	}
	return 0;
}
