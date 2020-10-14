#include <bits/stdc++.h>

long long c[20], a[20];
int n;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> n;
	c[0] = 1;
	for(int i = 1; i <= n; i++) std::cin >> c[i];
	std::reverse(c, c + n + 1);
	int ans = 0;
	for(int x = -10; x <= 10; x++) {
		int h = n;
		long long res = 0;
		for(int i = n; i >= 0; i--) {
			res *= x;
			res += c[i];
		}
		if(res == 0) {
			ans++;
			for(int i = 0; i <= n; i++) a[i] = c[i];
			int h = n;
			for(;;) {
				for(int i = 0; i < h; i++) {
					a[i] = a[i + 1] * (i + 1);
				}
				h--;
				while(h >= 0 && a[h] == 0) h--;
				if(h < 0) break;
				long long res = 0;
				for(int i = h; i >= 0; i--) {
					res *= x;
					res += a[i];
				}
				if(res == 0) ans++;
			}
		}
	}
	printf("%d\n", n - ans);
	return 0;
}
