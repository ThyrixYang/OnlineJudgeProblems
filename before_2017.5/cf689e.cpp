#include <bits/stdc++.h>

const long long mod = 1e9 + 7;
const int maxn = 1e6;
long long qpow(long long a, long long p) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % mod;
		a = a * a % mod;
		p >>= 1;
	}
	return ans;
}
long long fac[maxn],inv[maxn];
int n, k;
struct Point {
	int x, t;
	Point(int x = 0, int t = 0):x(x), t(t){}
	bool operator < (const Point &C) const {
		return x < C.x;
	}
}p[maxn];
long long C(int n, int k) {
	return fac[n] * inv[k] % mod * inv[n - k] % mod;
}
int main() {
	fac[0] = inv[0] = 1;
	for(int i = 1; i < maxn; i++) {
		fac[i] = fac[i - 1] * i % mod;
		inv[i] = qpow(fac[i], mod - 2);
	}
	int h = 0;
	std::cin >> n >> k;
	for(int i = 0; i < n; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		p[h++] = Point(l, 1);
		p[h++] = Point(r + 1, -1);
	}
	std::sort(p, p + h);
	long long ans = 0;
	int cnt = 0;
	long long last = -1e18;
	for(int i = 0; i < h; i++) {
		if(cnt >= k) ans = (ans + ((long long)p[i].x - last) * C(cnt, k)) % mod;
		cnt += p[i].t;
		last = p[i].x;
	}
	std::cout << ans;
	return 0;
}
