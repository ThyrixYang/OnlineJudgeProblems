#include <bits/stdc++.h>
long long lcm(long long a, long long b) {
	return a/ std::__gcd(a, b) * b;
}
int main() {
	freopen("./in", "r", stdin);
	long long res = 1;
	for(int i = 2; i < 41; i++) {
		res = lcm(i, res);
		printf("%lld\n", res);
	}
	return 0;
}
