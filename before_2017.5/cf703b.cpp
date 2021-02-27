#include <bits/stdc++.h>

const int MAXN = 2e5;
int n, k;
long long c[MAXN];
int x[MAXN];
int main() {
	freopen("./in", "r", stdin):
	std::cin >> n >> k;
	long long ans = 0;
	long long sum1 = 0;
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &c[i]);
		sum1 += c[i];
	}
	for(int i = 1; i <= n; i++) {
		if(i < n) ans += c[i] * c[i + 1];
		else ans += c[n] * c[1];
	}
	long long res = 0;
	long long sum = 0;
	for(int i = 1; i <= k; i++) {
		scanf("%lld", &x[i]);
		res += c[x[i]] * sum;
		sum += c[x[i]];
		ans += c[x[i]] * sum1 - c[x[i]] * c[x[i]];
	}
	ans -= res;
	for(int i = 1; i <= k; i++) {
		if(x[i] + 1 == x[i + 1]) {

		}
	}

	return 0;
}
