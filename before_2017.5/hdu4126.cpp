#include <bits/stdc++.h>

using namespace std;
#define tm szefad
const int MAXM = 1e5;
const int INF = 1e9;
struct edge {
	int to, w, next;
}E[MAXM];
const int MAXN = 3005;
int head[MAXN], eh;
void addEdge(int from, int to, int w) {
	E[eh].to = to, E[eh].w = w, E[eh].next = head[from];
	head[from] = eh++;
}
int N, M;
int mat[MAXN][MAXN];
int con[MAXN];
int in[MAXN];
int intree[MAXN][MAXN];
int mlen[MAXN][MAXN];
int ef[MAXN];
int tm;
long long tlen;
void Prim() {
	tlen = 0;
	eh = 0;
	tm++;
	std::memset(head, -1, sizeof(int) * N);
	std::memset(con, 0x3f, sizeof(int) * N);
	std::memset(in, 0, sizeof(int) * N);
	int v = 0;
	for(int t = 0; t < N - 1; t++) {
		in[v] = 1;
		con[v] = INF;
		int nt, mn = INF;
		for(int i = 0; i < N; i++) {
			if(!in[i]) {
				if(con[i] > mat[v][i]) {
					ef[i] = v;
					con[i] = mat[v][i];
				}
				if(con[i] < mn) {
					mn = con[i];
					nt = i;
				}
			}
		}
		addEdge(ef[nt], nt, mn);
		addEdge(nt, ef[nt], mn);
		tlen += mn;
		intree[ef[nt]][nt] = intree[nt][ef[nt]] = tm;
		v = nt;
	}
}
int dfs(int st, int v, int f = -1) {
	int ans = INF;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		int w = E[i].w;
		if(u == f) continue;
		int d = dfs(st, u, v);
		mlen[v][u] = mlen[u][v] = std::min(d, mlen[v][u]);
		ans = std::min(ans, d);
	}
	if(st != f) ans = std::min(ans, mat[st][v]);
	return ans;
}
void gao() {
	for(int i = 0; i < N; i++) 
		for(int j = 0; j < N; j++) 
			mlen[i][j] = INF;
	for(int i = 0; i < N; i++) {
		dfs(i, i);
	}
}
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d%d", &N, &M)) {
		if(N == 0 && M == 0) break;
		for(int i = 0; i < N; i++) 
			for(int j = 0; j < N; j++) 
				mat[i][j] = 1e9;
		for(int i = 0; i < M; i++) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			mat[x][y] = mat[y][x] = min(mat[x][y], z);
		}
		Prim();
		gao();
		int Q;
		scanf("%d", &Q);
		double sum = 0;
		int K = Q;
		while(K--) {
			int X, Y, Z;
			scanf("%d%d%d", &X, &Y, &Z);
			if(intree[X][Y] == tm) {
				long long len1 = std::min(tlen + Z - mat[X][Y],
						tlen + mlen[X][Y] - mat[X][Y]);
				sum += len1;
			} else {
				sum += tlen;
			}
		}
		printf("%.4f\n", sum / Q);
	}
	return 0;
}
