#include <bits/stdc++.h>

using namespace std;
const int MAXN = 1005;
int N, M, W;
int wei[MAXN];
int bu[MAXN];
vector<int> G[MAXN];
int dp[MAXN];
int tmp[MAXN];
int vis[MAXN];
int sw, sb;
void dfs(int v) {
	if(vis[v]) return;
	vis[v] = 1;
	sw += wei[v];
	sb += bu[v];
	for(int i = 0; i < W; i++) {
		if(i + wei[v] <= W) {
			int t = i + wei[v];
			tmp[t] = max(tmp[t], dp[i] + bu[v]);
		}
	}
	for(int i = 0; i < (int) G[v].size(); i++) {
		int u = G[v][i];
		dfs(u);
	}
}
int main() {
	freopen("in.txt", "r", stdin);
	cin >> N >> M >> W;
	for(int i = 1; i <= N; i++) {
		scanf("%d", &wei[i]);
	}
	for(int i = 1; i <= N; i++) {
		scanf("%d", &bu[i]);
	}
	for(int i = 0; i < M; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for(int i = 1; i <= N; i++) {
		if(!vis[i]) {
			sw = sb = 0;
			memset(tmp, 0, sizeof tmp);
			dfs(i);
			for(int j = W - sw; j >= 0; j--) {
				dp[j + sw] = max(dp[j + sw], dp[j] + sb);
			}
			for(int j = 0; j <= W; j++) {
				dp[j] = max(dp[j], tmp[j]);
			}
		}
	}
	int ans = 0;
	for(int i = 0; i <= W; i++) {
		ans = max(ans, dp[i]);
	}
	cout << ans << endl;
	return 0;
}
