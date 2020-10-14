#include <bits/stdc++.h>

const int MAXN = 500;
std::vector<int> G[MAXN];
int n, m;
void addEdge(int a, int b) {
	G[a].push_back(b);
	G[b].push_back(a);
}
int col[MAXN];
int cnt[MAXN][2];
int find(int);
void dfs1(int v, int c = 0) {
	col[v] = c;
	cnt[find(v)][c]++;
	for(int i = 0; i < G[v].size(); i++) {
		int u = G[v][i];
		if(col[u] == -1) dfs1(u, c ^ 1);
	}
}
int fa[MAXN];
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
int mat[MAXN][MAXN];
std::string pos[MAXN];
std::vector<int> cat[MAXN];
int main() {
	freopen("./in", "r", stdin);
	std::cin >> n;
	std::memset(col, -1, sizeof col);
	for(int i = 1; i <= n; i++) {
		fa[i] = i;
		std::cin >> pos[i];
		int k;
		scanf("%d", &k);
		for(int j = 0; j < k; j++) {
			int x;
			scanf("%d", &x);
			cat[i].push_back(x);
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < (int)cat[i].size(); j++) {
			int x = cat[i][j];
			if(pos[i] != pos[x]) mat[x][i] = mat[i][x] = 1;
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			if(pos[i] != pos[j]) {
				for(int x = 0, y = 0; x < cat[i].size(); x++) {
					while(y < cat[j].size() && cat[j][y] < cat[i][x]) y++;
					if(y < cat[j].size() && cat[j][y] == cat[i][x]) mat[i][j] = mat[j][i] = 1;
				}
			}
		}
	}
	int f = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			if(mat[i][j]) addEdge(i, j), fa[find(i)] = find(j), f = 1;
		}
	}
	if(!f){
		puts("1");
		puts("1");
		return 0;
	}
	int res = 0;
	for(int i = 1; i <= n; i++) {
		if(col[i] == -1) {
			dfs1(i);
			int x = find(i);
			if(cnt[x][0] > cnt[x][1]) res += cnt[x][1];
			else res += cnt[x][0];
		}
	}
	printf("%d\n", res);
	for(int i = 1; i <= n; i++) {
		int x = find(i);
		if(cnt[x][1] < cnt[x][0] && col[i] == 1) printf("%d ", i);
		else if(cnt[x][0] <= cnt[x][1] && col[i] == 0) printf("%d ", i);
	}
	return 0;
}
