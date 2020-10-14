#include <bits/stdc++.h>

template<class T1, class T2>
class Pair{
	public:
		T1 first;
		T2 second;
		Pair(const T1& a, const T2& b);
		Pair(){}
		bool operator < (const Pair &A);
};
template<class T1, class T2>
Pair<T1, T2>::Pair(const T1& a, const T2& b) {
	first = a;
	second = b;
}
template<class T1, class T2>
bool Pair<T1, T2>::operator < (const Pair &A) {
	if(A.first != first) return first < A.first;
	return second < A.second;
}
const int MAXN = 2e4 + 300;
const int MAXE = 1e6;
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
int N, B, Q;
Pair<int, int>  A[MAXN];
int main() {
	freopen("./in", "r", stdin);
	clearGraph();
	std::cin >> N >> B >> Q;
	for(int i = 0; i < Q; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		A[i].first = x;
		A[i].second = y;
	}
	A[Q++] = Pair<int, int>(0, 0);
	A[Q++] = Pair<int, int>(B, N);
	std::sort(A, A + Q);
	int S = MAXN - 1, T = S - 1;
	int sz = N + 1;
	for(int i = 1; i < Q; i++) {
		if(A[i].first == A[i - 1].first
				&& A[i].second != A[i - 1].second) {
			puts("unfair");
			return 0;
		}
		if(A[i].second < A[i - 1].second) {
			puts("unfair");
			return 0;
		}
		for(int j = A[i - 1].first + 1; j <= A[i].first; j++) {
			addEdge(sz, j, 1);
		}
		addEdge(S, sz, std::min(A[i].second - A[i - 1].second, 
								A[i].first - A[i - 1 ].first));
		sz++;
	}
	int s0 = T - 1, s1 = s0 - 1, s2 = s1 - 1, s3 = s2 - 1, s4 = s3 - 1;
	for(int i = 1; i <= B; i++) {
		if(i % 5 == 0) {
			addEdge(i, s0, 1);
		} else if(i % 5 == 1) {
			addEdge(i, s1, 1);
		} else if(i % 5 == 2) {
			addEdge(i, s2, 1);
		} else if(i % 5 == 3) {
			addEdge(i, s3, 1);
		} else {
			addEdge(i, s4, 1);
		}
	}
	addEdge(s0, T, N / 5);
	addEdge(s1, T, N / 5);
	addEdge(s2, T, N / 5);
	addEdge(s3, T, N / 5);
	addEdge(s4, T, N / 5);
	int res = dinic(S, T);
	if(res == N) puts("fair");
	else puts("unfair");
	return 0;
}
