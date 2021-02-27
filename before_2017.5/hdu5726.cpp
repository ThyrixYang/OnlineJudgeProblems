#include <bits/stdc++.h>

const int MAXN = 2e5;
int T, n, cas = 0;
int a[MAXN];
int b[20][MAXN];
void ST() {
	for(int i = 1; i <= n; i++) b[0][i] = a[i];
	for(int k = 1; k < 20; k++) {
		int d = 1 << (k - 1);
		for(int i = 1; i <= n; i++) {
			if(i + d > n) break;
			b[k][i] = std::__gcd(b[k - 1][i], b[k - 1][i + d]);
		}
	}
}
int getGCD(int s, int t) {
	int d = t - s;
	int k = 0;
	while((1 << (k + 1)) <= d) k++;
	return std::__gcd(b[k][s], b[k][t - (1 << k)]);
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		ST();
		std::map<int, long long> M;
		for(int i = 1; i <= n; i++) {
			for(int j = i + 1; j <= n + 1; j++) {
				int d = getGCD(i, j);
				int l = j, r = n + 2;
				while(r - l  > 1) {
					int mid = (r + l) >> 1;
					if(getGCD(i, mid) >= d) l = mid;
					else r = mid;
				}
				M[d] += l - j + 1;
				j = l;
			}
		}
		printf("Case #%d:\n", ++cas);
		int q;
		scanf("%d", &q);
		while(q--) {
			int l, r;
			scanf("%d%d", &l, &r);
			int g = getGCD(l, r + 1);
			printf("%d %lld\n", g, M[g]);
		}
	}
	return 0;
}
