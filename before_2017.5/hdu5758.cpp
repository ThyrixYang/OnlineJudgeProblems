#include <bits/stdc++.h>

const int MAXN = 2e5;
int T, n;
std::vector<int> G[MAXN];
int cnt[MAXN];
int ans = 0;
void dfs(int v, int f = -1) {
	int g = 0;
	for(auto &u: G[v]) {
		if(u == f) continue;
		g = 1;
		dfs(u, v);
		cnt[v] += cnt[u];
	}
	if(!g) cnt[v]++;
	if(f == -1) return;
	if(cnt[v] & 1) ans++;
	else ans += 2;
}
int main() {
	std::cin >> T;
	while(T--) {
		ans = 0;
		scanf("%d", &n);
		if(n == 1) {
			puts("0");
			continue;
		}
		for(int i = 1; i <= n; i++) G[i].clear();
		memset(cnt, 0, sizeof (int) * (n + 3));
		for(int i = 0; i < n - 1; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			G[x].push_back(y);
			G[y].push_back(x);
		}
		if(n == 2) {
			puts("1");
			continue;
		}
		dfs(1);
		printf("%d\n", ans);
	}
	return 0;
}
