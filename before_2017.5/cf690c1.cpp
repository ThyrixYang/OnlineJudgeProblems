#include <bits/stdc++.h>

const int MAXN = 1e6;
int n, m;
int fa[MAXN];
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
int main() {
	for(int i = 0; i < MAXN; i++) fa[i] = i;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		fa[find(a)] = find(b);
	}
	if(m != n - 1) {
		puts("no");
		return 0;
	}
	for(int i = 1; i <= n; i++) {
		if(find(i) != find(1)) {
			puts("no");
			return 0;
		}
	}
	puts("yes");
	return 0;
}
