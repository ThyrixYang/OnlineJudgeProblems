#include <bits/stdc++.h>

const long long MOD = 1e9 + 7;
const int MAXN = 1005;
struct BIT {
	long long a[MAXN][MAXN];
	void add(int i, int j, long long x) {
		for(; i < MAXN; i += i & -i) {
			for(int y = j; y < MAXN; y += y & -y) {
				a[i][y] += x;
				if(a[i][y] >= MOD) a[i][y] -= MOD;
			}
		}
	}
	long long sum(int x, int y) {
		long long ans = 0;
		for(; x > 0; x -= x & - x) {
			for(int j = y; j > 0; j -= j & -j) {
				ans += a[x][j];
				if(ans >= MOD) ans -= MOD;
			}
		}
		return ans;
	}
	void clear() {
		std::memset(a, 0, sizeof a);
	}
}B;
int n,m;
int a[MAXN], b[MAXN];
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d%d", &n, &m) != EOF) {
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
		long long ans = 0;
		B.clear();
		B.add(1, 1, 1);
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				if(a[i] == b[j]) {
					long long res = B.sum(i, j);
					ans += res;
					if(ans >= MOD) ans -= MOD;
					B.add(i + 1, j + 1, res);
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
