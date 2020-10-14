#include <bits/stdc++.h>

const int MAXN = 1e6;
int n;
long long a[MAXN];
struct BIT {
	int a[MAXN];
	void add(int p, int x) {
		while(p < MAXN) a[p] += x, p += p & -p;
	}
	int sum(int p) {
		int ans = 0;
		while(p > 0) ans += a[p], p -= p & -p;
		return ans;
	}
}B;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> n;
	for(int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		B.add(x, 1);
	}
	int q;
	scanf("%d", &q);
	while(q--) {
		int x;
		scanf("%d", &x);
		x = std::min(x, MAXN - 3);
		printf("%d\n", B.sum(x));
	}
	return 0;
}
