#include <bits/stdc++.h>

using namespace std;
typedef std::pair<int, int> P;
const int MAXN = 2e5 + 300;
const int MAXM = MAXN * 2;
int W[MAXM], C[MAXM];
int A[MAXN], B[MAXN];
int N, M;
int es[MAXM];
int used[MAXN];
struct edge {
	int to, w, id, next;
}E[MAXM];
int head[MAXN], eh;
void addEdge(int from, int to, int id, int w) {
	E[eh].to = to, E[eh].w = w, E[eh].id = id, E[eh].next = head[from];
	head[from] = eh++;
}
int faa[MAXN];
int find(int x) {
	if(x == faa[x]) return x;
	return faa[x] = find(faa[x]);
}
bool cmp(int a, int b) {
	return W[a] < W[b];
}
int fa[20][MAXN];
P mlen[20][MAXN];
int dep[MAXN];
void dfs(int v, int f = 0, int d = 0) {
	dep[v] = d;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		int w = E[i].w;
		int id = E[i].id;
		if(u == f) continue;
		dfs(u, v, d + 1);
		fa[0][u] = v;
		mlen[0][u] = P(w, id);
	}
}
void lca_pre() {
	for(int k = 1; k < 20; k++) {
		for(int i = 1; i <= N; i++) {
			fa[k][i] = fa[k - 1][fa[k - 1][i]];
			mlen[k][i] = max(mlen[k - 1][i], mlen[k - 1][fa[k - 1][i]]);
		}
	}
}
P lca(int a, int b) {
	if(dep[a] < dep[b]) swap(a, b);
	P res = P(0, 0);
	for(int k = 19; k >= 0; k--) {
		if((dep[a] - dep[b]) & (1 << k)) {
			res = max(res, mlen[k][a]);
			a = fa[k][a];
		}
	}
	if(a == b) return res;
	for(int k = 19; k >= 0; k--) {
		if(fa[k][a] != fa[k][b]) {
			res = max(res, mlen[k][a]);
			res = max(res, mlen[k][b]);
			a = fa[k][a];
			b = fa[k][b];
		}
	}
	return res;
}
int S;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N >> M;
	for(int i = 0; i < M; i++) scanf("%d", &W[i]);
	for(int i = 0; i < M; i++) scanf("%d", &C[i]);
	for(int i = 0; i < M; i++) scanf("%d%d", &A[i], &B[i]);
	std::cin >> S;
	for(int i = 0; i < M; i++) faa[i] = es[i] = i;
	std::sort(es, es + M, cmp);
	std::memset(head, -1, sizeof head);
	long long tol = 0;
	for(int i = 0; i < M; i++) {
		if(find(A[es[i]]) == find(B[es[i]])) continue;
		tol += W[es[i]];
		faa[find(A[es[i]])] = find(B[es[i]]);
		used[i] = 1;
		addEdge(A[es[i]], B[es[i]], i, W[es[i]]);
		addEdge(B[es[i]], A[es[i]], i, W[es[i]]);
	}
	dfs(1);
	lca_pre();
	int e, d = 1e9;
	for(int i = 0; i < M; i++) {
		if(used[i]) {
			int t = -S / C[es[i]];
			if(t < d) {
				d = t;
				e = i;
			}
		} else {
			P res = lca(A[es[i]], B[es[i]]);
			int t = -S / C[es[i]] + W[es[i]] - res.first;
			if(t < d) {
				d = t;
				e = i;
			}
		}
	}
	std::cout << tol + d << std::endl;
	if(!used[e]) {
		int p = lca(A[es[e]], B[es[e]]).second;
		used[p] = 0;
		used[e] = 1;
	}
	for(int i = 0; i < M; i++) {
		if(used[i]) {
			if(i == e) {
				printf("%d %d\n", es[i] + 1, W[es[i]] - S / C[es[i]]);
			} else {
				printf("%d %d\n", es[i] + 1, W[es[i]]);
			}
		}
	}
	return 0;
}
