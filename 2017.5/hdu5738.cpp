#include <bits/stdc++.h>

const int MAXN = 1005;
const long long MOD = 1e9 + 7;
long long qpow(long long a, long long p) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
int n, T;
std::pair<int, int> ps[MAXN], ns[MAXN];
long long ans;
void cal(int s, int cnt) {
	int h = 0;
	for(int i = s + 1; i < n; i++) {
		int dx = ps[i].first - ps[s].first;
		int dy = ps[i].second - ps[s].second;
		int g = std::abs(std::__gcd(dx, dy));
		dx /= g, dy /= g;
		ns[h++] = std::make_pair(dx, dy);
	}
	std::sort(ns, ns + h);
	for(int i = 0; i < h; i++) {
		int j = i;
		while(j < h && ns[i] == ns[j]) j++;
		ans += (qpow(2, cnt) - 1) * (qpow(2, j - i) - 1) % MOD;
		ans %= MOD;
		i = j - 1;
	}
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		ans = 0;
		scanf("%d", &n);
		for(int i = 0; i < n; i++)
			scanf("%d%d", &ps[i].first, &ps[i].second);
		std::sort(ps, ps + n);
		for(int i = 0; i < n; i++) {
			int j = i;
			while(j < n && ps[i] == ps[j]) j++;
			if(j - i >= 2) ans += qpow(2, j - i) - j + i - 1;
			ans %= MOD;
			cal(j - 1, j - i);
			i = j - 1;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
