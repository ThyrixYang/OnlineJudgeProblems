#include <bits/stdc++.h>

const int MAXN = 70000;
int T;
int a[10];
int n, k;
long long dp[20][
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		std::cin >> n >> k;
		for(int i = 0; i < n; i++) scanf("%d", &a[i]);
		std::sort(a, a + n);
	}
	return 0;
}
