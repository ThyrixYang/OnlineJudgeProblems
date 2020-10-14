#include <bits/stdc++.h>

int a[3];
int sg[1005];
int vis[1005];
int fib[1005];
int main() {
	freopen("in", "r", stdin);
	fib[0] = 1, fib[1] = 2;
	int h = 2;
	for(;;) {
		fib[h] = fib[h - 1] + fib[h - 2];
		if(fib[h] > 1000) break;
		h++;
	}
	int tm = 0;
	for(int i = 1; i <= 1000; i++) {
		tm++;
		for(int j = 0; j < h; j++) {
			if(i - fib[j] < 0) break;
			vis[sg[i - fib[j]]] = tm;
		}
		for(int j = 0; j <= h; j++) {
			if(vis[j] != tm) {
				sg[i] = j;
				break;
			}
		}
	}
	while(scanf("%d%d%d", &a[0], &a[1], &a[2])) {
		if(a[0] == 0 && a[1] == 0 && a[2] == 0) break;
		int ans = (sg[a[0]] ^ sg[a[1]] ^ sg[a[2]]);
		if(ans) puts("Fibo");
		else puts("Nacci");
	}
	return 0;
}