#include <bits/stdc++.h>

int N, M, K;
char B[70][70];
int cnt[10000];
int id[70][70];
int drx[] = {0, 0, -1, 1};
int dry[] = {-1, 1, 0, 0};
void dfs(int x, int y, int c) {
	if(id[x][y] != -1) return;
	id[x][y] = c;
	cnt[c]++;
	for(int i = 0; i < 4; i++) {
		int dx = x + drx[i];
		int dy = y + dry[i];
		if(dx < 0 || dx >= N || dy < 0 || dy >= M) continue;
		if(B[dx][dy] == '.') dfs(dx, dy, c);
	}
}
void col(int x, int y, int c) {
	id[x][y] = 0;
	B[x][y] = '*';
	for(int i = 0; i < 4; i++) {
		int dx = x + drx[i];
		int dy = y + dry[i];
		if(dx < 0 || dx >= N || dy < 0 || dy >= M) continue;
		if(id[dx][dy] == c) col(dx, dy, c);
	}
}
int st[10000];
int p[10000], ph;
bool cmp(int a, int b) {
	return cnt[a] < cnt[b];
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N >> M >> K;
	std::memset(id, -1, sizeof id);
	for(int i = 0; i < N; i++) {
		scanf("%s", B[i]);
	}
	for(int i = 0; i < N; i++) {
		if(B[i][0] == '.') dfs(i, 0, 0);
		if(B[i][M - 1] == '.') dfs(i, M - 1, 0);
	}
	for(int i = 0; i < M; i++) {
		if(B[0][i] == '.') dfs(0, i, 0);
		if(B[N - 1][i] == '.') dfs(N - 1, i, 0);
	}
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			if(B[i][j] == '.' && id[i][j] == -1) {
				p[ph] = ph + 1;
				ph++;
				st[ph] = i * M + j;
				dfs(i, j, ph);
			}
		}
	}
	std::sort(p, p + ph, cmp);
	int cc = ph;
	int res = 0;
	for(int i = 0; i < ph && cc > K; i++) {
		cc--;
		int x = st[p[i]] / M, y = st[p[i]] % M;
		col(x, y, p[i]);
		res += cnt[p[i]];
	}
	std::cout << res << std::endl;
	for(int i = 0; i < N; i++) {
		printf("%s\n", B[i]);
	}
	return 0;
}
