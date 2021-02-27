#include <bits/stdc++.h>

const int MAXN = 27;
int n;
std::vector<int> G[MAXN];
char s[MAXN];
int bl[MAXN];
int v[MAXN], vh;
int ans;
int col[MAXN];
int a[60][4];
bool dfs(int v, int c) {
	col[v] = c;
	if(bl[v] == 1 && c == 1) return 0;
	if(bl[v] == 2 && c == 0) return 0;
	for(int i = 0; i < G[v].size(); i++) {
		int u = G[v][i];
		if(bl[u] == 3) continue;
		if(col[u] == -1 && !dfs(u, c ^ 1)) return 0;
		if(bl[u] != 3 && col[u] != c ^ 1) {
			return 0;
		}
	}
	return 1;
}
bool check() {
	std::memset(bl, -1, sizeof bl);
	for(int i = 0; i < vh; i++) {
		bl[v[i]] = 3;
	}
	for(int i = 0; i < n; i++) {
		if(a[i][3] == 2) {
			if(bl[a[i][0]] != -1 && bl[a[i][0]] != a[i][2]) return 0;
			bl[a[i][0]] = a[i][2];
			if(bl[a[i][1]] != -1 && bl[a[i][1]] != a[i][2]) return 0;
			bl[a[i][1]] = a[i][2];
		} else if(a[i][3] == 0) {
			if(bl[a[i][0]] != 3) {
				if(bl[a[i][0]] != -1 && bl[a[i][0]] != (a[i][2] ^ 1)) return 0;
				bl[a[i][0]] = a[i][2] ^ 1;
			} 
			if(bl[a[i][1]] != 3) {
				if(bl[a[i][1]] != -1 && bl[a[i][1]] != (a[i][2] ^ 1)) return 0;
				bl[a[i][1]] = a[i][2] ^ 1;
			}
		}
	}
	std::memset(col, -1, sizeof col);	
	for(int i = 0; i < 26; i++) {
		if(col[i] == -1 && (bl[i] == 1 || bl[i] == 2)) {
			int d;
			if(bl[i] == 1) d = dfs(i, 0);
			else d = dfs(i, 1);
			if(!d) {
				return 0;
			}
		}
	}
	for(int i = 0; i < 26; i++) {
		if(col[i] == -1 && bl[i] != 3) {
			if(!dfs(i, 0)){
				return 0;
			}
		}
	}
	return 1;
}
void dfs(int p) {
	if(vh == 3) {
		if(check()) {
			ans++;
		}
		return;
	}
	if(p == 26) return;
	v[vh++] = p;
	dfs(p + 1);
	vh--;
	dfs(p + 1);
}
int cas;
int main() {

	freopen("./in", "r", stdin);

	while(std::cin >> n) {
		printf("cas %d\n", ++cas);
		for(int i = 0; i < MAXN; i++) G[i].clear();
		for(int i = 0; i < n; i++) {
			scanf("%s", s);
			a[i][0] = s[0] - 'A';
			a[i][1] = s[1] - 'A';
			scanf("%d%d", &a[i][2], &a[i][3]);
			if(a[i][3] == 1) {
				G[a[i][0]].push_back(a[i][1]);
				G[a[i][1]].push_back(a[i][0]);
			}
		}
		ans = 0;
		dfs(0);
		printf("%d\n", ans);
	}

	return 0;
}
