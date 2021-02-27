#include <bits/stdc++.h>

const long long MOD = 2333333;
const long long H = 907;
const int MAXN = 1e7 + 400;
//int vis[MOD];
int w[80];
int a[80];
int n, seed;
int fa[MAXN];
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
bool cmp(int a,int b) {
	return w[a] < w[b];
}
long long ans = 0;
void unite(int x,int y, int w) {
	if(find(x) == find(y)) return;
	ans += w;
	fa[find(x)] = find(y);
}
void cal(int wi, int p) {
	int s1, s2;
	if(p == 0) {}
	if(p == 1) {}
	if(p == 2 && n >= 2) unite(2, 1, wi);
	if(p == 3 && n >= 3) unite(3, 1, wi);
	if(p == 4 && n >= 3) unite(3, 2, wi);
	if(p == 5 && n >= 4) unite(4, 1, wi);
	if(p == 6 && n >= 4) unite(4, 2, wi);
	if(p == 7 && n >= 4) unite(4, 3, wi);
	if(p == 8 && n >= 5) unite(5, 1, wi);
	if(p == 9 && n >= 5) unite(5, 2, wi);
	if(p == 10 && n >= 5) unite(5, 3, wi);
	if(p == 11 && n >= 5) unite(5, 4, wi);
	if(p <= 11) {
		s1 = p / 6 + 13;
		s2 = p % 6 + s1 - 5;
	} else {
		s1 = p / 6 + 4;
		s2 = p % 6 + s1 - 5;
	}
	for(int i = s1, j = s2; i <= n; i += 9, j += 9)
		unite(i, j, wi);
}
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d%d", &n, &seed) != EOF) {
		for(int i = 1; i <= n; i++) fa[i] = i;
		ans = 0;
		w[0] = seed;
		a[0] = 0;
		for(int i = 1; i < 80; i++) w[i] = w[i - 1] * H % MOD, a[i] = i, printf("%d %d\n", i, w[i]);
		std::sort(a, a + 54, cmp);
		/*for(int i = 0; i < 54; i++) {
			printf("%d %d %d\n", i, a[i], w[a[i]]);
		}*/
		for(int i = 0; i < 54; i++) {
			int id = a[i];
			int we = w[id];
			cal(we, id);
		}
		printf("%lld\n", ans);
	}

	/*for(int s = 1; s < 100; s++) {
		std::memset(vis, 0, sizeof vis);
		long long x = s;
		int cnt = 0;
		for(;;) {
			if(vis[x]) break;
			cnt++;
			vis[x] = 1;
			x = x * H % MOD;
		}
		printf("%d %d\n", s, cnt);
	}*/
	return 0;
}
