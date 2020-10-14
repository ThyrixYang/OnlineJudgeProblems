#include <bits/stdc++.h>

const int MAXN = 2e5 + 3000;
int T;
long long n, m;
int has[MAXN];
int X[MAXN], Y[MAXN];
int main() {
	std::cin >> T;
	while(T--) {
		scanf("%lld%lld", &n, &m);
		for(int i = 0; i < n; i++) scanf("%d%d", &X[i], &Y[i]);
		if(n * (n - 1) / 2 > 2 * m) {
			puts("YES");
			continue;
		}
		std::memset(has, 0, sizeof has);
		int ans = 0;
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				if(++has[std::abs(X[i] - X[j]) + std::abs(Y[i] - Y[j])] == 2) {
					ans = 1;
				}
			}
		}
		if(ans) puts("YES");
		else puts("NO");
	}
	return 0;
}
