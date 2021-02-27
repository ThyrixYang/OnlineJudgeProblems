#include <bits/stdc++.h>

const int MAXN = 1005;
long long n;
double c[MAXN];
double fac[MAXN];
int main () {
	for(int i = 2; i < MAXN; i++) fac[i] = fac[i - 1] + i * (i - 1);
	while(std::cin >> n) {
		for(int i = 1; i <= n; i++) scanf("%lf", &c[i]);
		if(n == 1) {
			printf("%.5f\n", c[1]);
			continue;
		}
		if(n == 2) {
			printf("%.5f\n", (c[1] + c[2]) / 2);
			continue;
		}
		double ans = 0;
		for(int i = 1; i <= n; i++) {
			if(i == 1 || i == n) {
				ans += 0.5 * c[i];
			}else {
				ans += fac[n - 1] * c[i] / ((double)n * (n - 1) * (n - 2));
			}
		}
		printf("%.5f\n", ans);
	}
	return 0;
}
