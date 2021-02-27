#include <bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 3000;
int N;
vector<int> G[MAXN];
int col[MAXN];
int p[MAXN][2];
void dfs(int v, int c) {
	if(col[v] != -1) return;
	col[v] = c;
	for(int i = 0; i < (int) G[v].size(); i++) {
		int u = G[v][i];
		dfs(u, c ^ 1);
	}
}
int main() {
	freopen("in.txt", "r", stdin);
	memset(col, -1, sizeof col);
	cin >> N;
	for(int i = 0; i < N; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		p[i][0] = x;
		p[i][1] = y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for(int i = 1; i <= N; i++) {
		G[2 * i - 1].push_back(2 * i);
		G[2 * i].push_back(2 * i - 1);
	}
	for(int i = 1; i <= 2 * N; i++) {
		dfs(i, 0);
	}
	for(int i = 0; i < N; i++) {
		int c1 = col[p[i][0]];
		int c2 = col[p[i][1]];
		if(!c1) c1 = 2;
		if(!c2) c2 = 2;
		printf("%d %d\n", c1, c2);
	}
	return 0;
}
