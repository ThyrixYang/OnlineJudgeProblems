#include <bits/stdc++.h>

const int MAXN = 1e6;
int ne[MAXN];
int n, q;
int del[MAXN];
int fa[MAXN];
int last[MAXN];
int find(int x) { 
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> n >> q;
	for(int i = 0; i < MAXN; i++) fa[i] = i;
	int p = 1;
	int cnt = 0;
	while(q--) {
		int t;
		scanf("%d", &t);
		if(t == 1) {
			int x;
			scanf("%d", &x);
			ne[p] = last[x];
			last[x] = p;
			p++;
			cnt++;
			printf("%d\n", cnt);
		} else if(t == 2) {
			int x;
			scanf("%d", &x);
			int y = last[x];
			while(y != 0 && !del[y]) {
				del[y] = 1;
				cnt--;
				fa[y] = y + 1;
				y = ne[y];
			}
			printf("%d\n", cnt);
		} else {
			int y = find(1);
			int x;
			scanf("%d", &x);
			while(y <= x) {
				del[y] = 1;
				fa[y] = y + 1;
				y = find(y);
				cnt--;
			}
			printf("%d\n", cnt);
		}
	}
	return 0;
}
