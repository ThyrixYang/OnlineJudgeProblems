#include <bits/stdc++.h>

const int MAXN = 2e5;
int n;
int a[MAXN];
std::map<long long, int> M;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> n;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	long long ans = 0;
	for(int i = n; i >= 1; i--) {
		ans += M[a[i]];
		for(int k = 0; k < 40; k++) {
			long long p = 1ll << k;
			if(p - a[i] < 0) continue;
			++M[p - a[i]];
		}
	}
	printf("%lld\n", ans);
	return 0;
}
