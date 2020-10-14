#include <bits/stdc++.h>

using namespace std;

#define fs first
#define se second
const int maxn=2e5;
int n;
int cnt[maxn];
vector<pair<int,int> > G[maxn];
int a[maxn];
int ans = 0;
int cut[maxn];
void dfs(int v, int f = -1, long long d = 0, long long md = 0) {
	for(int i = 0; i < G[v].size(); i++) {
		int u = G[v][i].fs;
		int len = G[v][i].se;
		if(u == f) continue;
		dfs(u, v, d + len, max(md, -d));
	}
	if(md + d - a[v] > 0) cut[v] = 1;
}
int count(int v, int f = -1) {
	if(cut[v]) return 0;
	int ans = 1;
	for(int i = 0; i < G[v].size(); i++) {
		int u = G[v][i].fs;
		if(u == f) continue;
		ans += count(u, v);
	}
	return ans;
}
int main() {
	freopen("./in","r",stdin);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= n - 1; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		G[i + 1].push_back(make_pair(x, y));
		G[x].push_back(make_pair(i + 1, y));
	}
	dfs(1);
	cout << n - count(1) << endl;
	return 0;
}
