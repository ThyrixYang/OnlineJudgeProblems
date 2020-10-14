#include <bits/stdc++.h>

const int MAXN = 2e5;
int T;
int n;
int ans[MAXN];
int cas = 0;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++){
			int x;
			scanf("%d", &x);
			ans[x] = std::abs(i - x);
		}
		printf("Case #%d:", ++cas);
		for(int i = 1; i <= n; i++) {
			printf(" %d", ans[i]);
		}
		puts("");
	}
	return 0;
}
