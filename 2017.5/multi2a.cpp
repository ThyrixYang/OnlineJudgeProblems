#include <bits/stdc++.h>

const int MAXN = 2e5;
int T, n;
long long w[MAXN];
long long gcd(long long a, long long b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}
int main() {
	std::cin >> T;
	while(T--) {
		scanf("%d", &n);
		long long sq = 0, sum = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%lld", &w[i]);
			sq += w[i] * w[i];
			sum += std::abs(w[i]);
		}
		long long up = n * sq - sum * sum;
		long long low = n;
		long long g = gcd(up, low);
		up /= g;
		low /= g;
		printf("%lld/%lld\n", up, low);
		
	}
	return 0;
}
