#include <bits/stdc++.h>

const int MAXN = 400;
int T;
int a[MAXN];
int dis[MAXN][MAXN];
int diff[MAXN][MAXN];
int n, k;
std::vector<int> G[MAXN];
int dic[MAXN], dh = 0;
int cnt[MAXN];
int cc = 0;
void dfs(int s, int v, int f = -1, int d = 0) {
	dis[s][v] = d;
	if(++cnt[a[v]] == 1) cc++;
	diff[s][v] = cc;
	for(int i = 0; i < G[v].size(); i++) {
		int u = G[v][i];
		if(u == f) continue;
		dfs(s, u, v, d + 1);
	}
	if(--cnt[a[v]] == 0) cc--;
}
double logFac[MAXN];
double ans;
double C(int p, int x) {
	return exp(logFac[p] - logFac[p - x] - logFac[x] - logFac[n] + logFac[k] + logFac[n - k]);
}
int main() {
	freopen("./in", "r", stdin);
	for(int i = 2; i < MAXN; i++) logFac[i] = logFac[i - 1] + log(i);
	std::cin >> T;
	while(T--) {
		std::cin >> n >> k;
		for(int i = 0; i <= n; i++) G[i].clear();
		for(int i = 0; i < n - 1; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			G[x].push_back(y);
			G[y].push_back(x);
		}
		dh = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), dic[dh++] = a[i];
		if(k == 0 || n < k || k == 1) {
			puts("0");
			continue;
		}
		std::sort(dic, dic + dh);
		dh = std::unique(dic, dic + dh) - dic;
		for(int i = 1; i <= n; i++) a[i] = std::lower_bound(dic, dic + dh, a[i]) - dic;
		for(int i = 1; i <= n; i++) dfs(i, i);
		ans = 0;
		for(int a = 1; a <= n; a++) {
			for(int b = a + 1; b <= n; b++) {
				int cho = 0;
				for(int i = 1; i <= n; i++) {
					if(std::max(dis[a][i], dis[i][b]) > dis[a][b]) continue;
					if(dis[a][i] == dis[a][b] && i < b) continue;
					if(dis[i][b] == dis[a][b] && i < a) continue;
					cho++;
				}
				if(cho < k) continue;
				ans += diff[a][b] * C(cho - 2, k - 2);
			}
		}
		printf("%.15f\n", ans);
	}
	return 0;
}
