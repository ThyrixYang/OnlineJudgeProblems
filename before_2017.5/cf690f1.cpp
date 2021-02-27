#include <bits/stdc++.h>

int n;
int cnt[100000];
int main() {
	std::cin >> n;
	for(int i = 0; i < n - 1; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		cnt[a]++;
		cnt[b]++;
	}
	long long ans = 0;
	for(int i = 1; i <= n; i++) {
		ans += cnt[i] * (cnt[i] - 1) / 2;
	}
	std::cout << ans;
	return 0;
}
