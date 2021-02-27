#include <bits/stdc++.h>

const int MAXN = 1e5 + 30;
long long n, k;
long long w[MAXN], f[MAXN];
long long l[MAXN], m[MAXN];
long long lt[MAXN], mt[MAXN];
long long tmp[2][MAXN];
int nt[70][MAXN];
int getnt(int x, long long k) {
	for(int i = 0; i < 70; i++) {
		if((1ll << i) > k) break;
		if((k >> i) & 1) x = nt[i][x];
	}
	return x;
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> n >> k;
	for(int i = 0; i < n; i++) {
		scanf("%lld", &f[i]);
		nt[0][i] = f[i];
	}
	for(int k = 1; k < 70; k++) {
		for(int i = 0; i < n; i++) {
			nt[k][i] = nt[k - 1][nt[k - 1][i]];
		}
	}
	for(int i = 0; i < n; i++) {
		scanf("%lld", &w[i]);
	}
	std::memset(m, 0x3f, sizeof m);
	for(int i = 0; i < n; i++) {
		lt[i] = w[i];
		mt[i] = w[i];
	}
	long long len = 0, lent = 1;
	while(k > 0) {
		if(k & 1) {
			for(int i = 0; i < n; i++) {
				int p = getnt(i, len);
				l[i] = l[i] + lt[p];
				m[i] = std::min(m[i], mt[p]);
			}
			len = len + lent;
		}
		for(int i = 0; i < n; i++) {
			int p = getnt(i, lent);
			tmp[0][i] = lt[i] + lt[p];
			tmp[1][i] = std::min(mt[i], mt[p]);
		}
		std::memcpy(lt, tmp[0], sizeof lt);
		std::memcpy(mt, tmp[1], sizeof mt);
		lent *= 2;
		k >>= 1;
	}
	for(int i = 0; i < n; i++) {
		printf("%lld %lld\n", l[i], m[i]);
	}
	return 0;
}
