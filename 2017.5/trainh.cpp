#include <bits/stdc++.h>

const int MAXN = 600;
int n;
int del[MAXN];
int x[MAXN], y[MAXN], v[MAXN];
int cas;
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d", &n) != EOF) {
		if(n == 0) break;
		std::memset(del, 0, sizeof del);
		int maxs = 0;
		for(int i = 0; i < n; i++) {
			scanf("%d%d%d", &x[i], &y[i], &v[i]);
		}
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				if(x[i] == x[j] && y[i] == y[j] && v[i] == v[j]) {
					del[i] = del[j] = 1;
				}
			}
		}
		for(int i = 0; i < n; i++) {
			if(v[i] > maxs && !del[i]) maxs = v[i];
		}
		printf("Case #%d: ", ++cas);
		for(int i = 0; i < n; i++) {
			if(v[i] > 0 && v[i] == maxs && !del[i]) printf("1");
			else printf("0");
		}
		puts("");
	}
	return 0;
}
