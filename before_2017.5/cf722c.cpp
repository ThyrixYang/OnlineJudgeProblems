#include <bits/stdc++.h>

const int MAXN = 1e5 + 300;
int N;
int a[MAXN];
int p[MAXN];
long long res[MAXN];
int fa[MAXN];
long long sum[MAXN];
int vis[MAXN];
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N;
	for(int i = 1; i <= N; i++) {
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= N; i++) {
		scanf("%d", &p[i]);
	}
	long long ans = 0;
	for(int i = N; i >= 1; i--) {
		res[i] = ans;
		int pos = p[i];
		fa[p[i]] = p[i];
		sum[p[i]] = a[p[i]];
		vis[p[i]] = 1;
		if(vis[pos + 1]) {
			sum[pos] += sum[find(pos + 1)];
			fa[find(pos + 1)] = pos;
		} 
		if(vis[pos - 1]) {
			sum[pos] += sum[find(pos - 1)];
			fa[find(pos - 1)] = pos;
		}
		ans = std::max(ans, sum[pos]);
	}
	for(int i = 1; i <= N; i++) {
		printf("%lld\n", res[i]);
	}
	return 0;
}
