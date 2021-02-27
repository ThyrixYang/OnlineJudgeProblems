#include <bits/stdc++.h>

const int MAXN = 1e6;
int n;
std::vector<int> G[MAXN];
int maxv[MAXN], up[MAXN];
int fa[MAXN], sz[MAXN];
int maxs[MAXN], maxson[MAXN];
void dfs(int v, int f = 0) {
	fa[v] = f;
	sz[v] = 1;
	for(auto &u: G[v]) {
		if(u == f) continue;
		dfs(u, v);
		sz[v] += sz[u];
		if(sz[u] > maxs[v]) {
			maxs[v] = sz[u];
			maxson[v] = u;
		}
	}
	maxv[v] = maxv[maxson[v]];
	if(sz[v] <= n / 2) maxv[v] = sz[v];
}
void dfs2(int v, int sum = 0, int down = 0) {
	up[v] = down;
	sum++;
	int m = 0, sm = 0, mid = 0, smid = 0;
	for(auto &u: G[v]) {
		if(u == fa[v]) continue;
		sum += sz[u];
		if(maxv[u] > sm) {
			sm = maxv[u];
			smid = u;
		}
		if(sm > m) {
			std::swap(sm, m);
			std::swap(smid, mid);
		}
	}
	for(auto &u: G[v]) {
		if(u == fa[v]) continue;
		int t = sum - sz[u];
		int tt;
		if(t <= n / 2) tt = t;
		else tt = 0;
		if(u != mid) dfs2(u, t, std::max(down, std::max(m, tt)));
		else dfs2(u, t, std::max(down, std::max(tt, sm)));
	}
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> n;
	for(int i = 0; i < n - 1; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	dfs(1);
	dfs2(1);
	for(int i = 1; i <= n; i++) {
		if(maxs[i] <= n / 2 && n - sz[i] <= n / 2) {
			printf("1 ");
		} else {
			if(maxs[i] > n / 2) {
				if(maxs[i] - maxv[maxson[i]] <= n / 2) printf("1 ");
				else printf("0 ");
			} else {
				if(n - sz[i] - up[i] <= n / 2) printf("1 ");
				else printf("0 ");
			}
		}
	}
	return 0;
}
