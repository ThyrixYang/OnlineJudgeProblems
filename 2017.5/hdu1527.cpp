#include <bits/stdc++.h>

const double g = (1 + sqrt(5.0)) / 2.0;
int a, b;
int main() {
	freopen("in", "r", stdin);
	while(scanf("%d%d", &a, &b) != EOF) {
		if(a > b) std::swap(a, b);
		int t = a / g;
		int f = 0;
		for(int x = t - 1; x <= t + 1; x++) {
			if(a == (int)(g * x) && b == a + x) {
				f = 1;
			}
		}
		if(f) puts("0");
		else puts("1");
	}
	return 0;
}