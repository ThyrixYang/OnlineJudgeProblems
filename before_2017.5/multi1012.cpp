#include <bits/stdc++.h>

const int MAXN = 6e4;
int n;
int a[MAXN];
int dic[MAXN], dh;
struct BIT {
	int a[MAXN];
	void add(int p, int x) {
		while(p < MAXN) a[p] += x, p += p & -p;
	}
	long long sum(int p) {
		long long ans = 0;
		while(p > 0) ans += a[p], p -= p & -p;
		return ans;
	}
	void clear() {
		std::memset(a, 0, sizeof a);
	}
}B;
long long ls[MAXN], lb[MAXN];
long long rs[MAXN], rb[MAXN];
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d", &n) != EOF) {
		dh = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), dic[dh++] = a[i];
		std::sort(dic, dic + dh);
		dh = std::unique(dic, dic + dh) - dic;
		for(int i = 1; i <= n; i++) {
			a[i] = std::lower_bound(dic, dic + dh, a[i]) - dic + 1;
		}
		B.clear();
		long long res1 = 0;
		long long res2 = 0;
		for(int i = 1; i <= n; i++) {
			B.add(a[i], 1);
			res1 += B.sum(a[i] - 1);
			res2 += i - B.sum(a[i]);
			ls[i] = B.sum(a[i] - 1);
			lb[i] = i - B.sum(a[i]);
		}
		B.clear();
		for(int i = n; i >= 1; i--) {
			B.add(a[i], 1);
			rs[i] = B.sum(a[i] - 1);
			rb[i] = n - i + 1 - B.sum(a[i]);
		}
		long long ans = res1 * res2;
		for(int i = 1; i <= n; i++) {
			ans -= ls[i] * lb[i];
			ans -= rs[i] * rb[i];
			ans -= rb[i] * lb[i];
			ans -= ls[i] * rs[i];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
