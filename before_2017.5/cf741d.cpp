#include <bits/stdc++.h>

const int MAXN = 1e6;
const int MAXE = 1e6;
struct Edge {
	int from, to, next, c;
	Edge(int _from = 0, int _to = 0, int _next = 0, int _c = 0) {
		from = _from;
		to = _to;
		next = _next;
		c = _c;
	}
}E[MAXE];
int head[MAXN], eh;
void addEdge(int from, int to, int c) {
	E[eh] = Edge(from, to, head[from], c);
	head[from] = eh++;
}
int N;
int val[MAXN];
void dfs0(int v, int k) {
	val[v] = k;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int c = E[i].c;
		int u = E[i].to;
		dfs0(u, k ^ (1 << c));
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	memset(head, -1, sizeof head);
	cin >> N;
	for(int i = 2; i <= N; i++) {
		int p;
		char c;
		scanf("%d%c", &p, &c);
		c -= 'a';
		addEdge(p, i, c);
		addEdge(i, p, c);
	}
	dfs0(1, 0);
	return 0;
}
