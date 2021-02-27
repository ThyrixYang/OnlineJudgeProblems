#include <bits/stdc++.h>

long long h, a, b, k;
int cas;
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%lld%lld%lld%lld", &h, &a, &b, &k)) {
		if(h == 0 && a == 0 && b == 0 && k == 0) {
			break;
		}
		printf("Case #%d: ", ++cas);
		if(h <= a) puts("YES");
		else if(h - (a - b) * (k - 1) - a <= 0) puts("YES");
		else if((a - b) * k - b > 0) puts("YES");
		else puts("NO");
	}
	return 0;
}
