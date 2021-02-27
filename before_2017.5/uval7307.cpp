#include <bits/stdc++.h>

const int MAXN = 600;
int N, P;
int cnt[MAXN];
int cut[MAXN], ch;
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d%d", &N, &P) != EOF) {
		if(N == 0 && P == 0) break;
		std::memset(cnt, 0, sizeof cnt);
		for(int i = 0; i < N; i++) {
			double x;
			scanf("%lf", &x);
			x *= 100;
			x += 1e-6;
			int y = x;
			cnt[y]++;
		}
		for(int i = 1; i <= 400; i++) cnt[i] += cnt[i - 1];
		long long ans = 0;
		for(int low = 250; low <= 400; low++) {
			for(int len = 1; len + low <= 400 + 1; len++) {
				ch = 0;
				int p = low;
				while(p <= 400) {
					cut[ch++] = cnt[std::min(400, p + len - 1)] - cnt[p - 1];
					p += len;
				}
				for(int sc = 1; sc <= 99; sc++) {
					int l = 0, r = 100 - sc;
					while(r - l > 1) {
						int mid = (r + l) >> 1;
						if(mid * (ch - 1) + sc > 100) r = mid;
						else {
							int res = 0;
							int cost = sc;
							for(int k = 0; k < ch; k++) {
								res += cost * cut[k];
								cost += mid;
							}
							if(res > P) r = mid;
							else l = mid;
						}
					}
					int p1 = r;
					l = 0, r = 100 - sc;
					while(r - l > 1) {
						int mid = (r + l) >> 1;
						if(mid * (ch - 1) + sc > 100) r = mid;
						else {
							int res = 0;
							int cost = sc;
							for(int k = 0; k < ch; k++) {
								res += cost * cut[k];
								cost += mid;
							}
							if(res >= P) r = mid;
							else l = mid;
						}
					}
					ans += p1 - r;
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
