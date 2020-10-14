#include <bits/stdc++.h>

const int MAXN = 1e5 + 3000;
const int MAXE = 1e6;
struct edge {
	int to, w, next;
}E[MAXE];
int head[MAXN], eh;
void addEdge(int from, int to, int w) {
	E[eh].to = to, E[eh].w = w, E[eh].next = head[from];
	head[from] = eh++;
}
int cut[MAXN];
int cntx;
void count(int v, int f = -1) {
	cntx++;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(cut[u] || u == f) continue;
		count(u, v);
	}
}
int center;
int getCenter(int v, int f = -1) {
	int cnt = 1;
	int maxs = 0;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(u == f || cut[u]) continue;
		int c = getCenter(u, v);
		cnt += c;
		maxs = std::max(maxs, c);
	}
	if(maxs <= cntx / 2 && cntx - cnt <= cntx / 2) center = v;
	return cnt;
}

std::map<int, int> M1, M2;
std::map<int, int> S1, S2;
void dfs1(int v, long long down = 1, int f = -1) {
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;

	}

}
long long ans = 0;
void solve(int v) {
	cut[v] = 1;
	M1.clear();
	M2.clear();
	
}
int N, M;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N >> M;
	for(int i = 0; i < N - 1; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		addEdge(x, y, z);
		addEdge(y, x, z);
	}
	
	return 0;
}
