#include <bits/stdc++.h>

const int MAXN = 2e5;
int n;
int a[MAXN];
int main() {
	std::cin >> n;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	int ans = 1;
	int cnt = 1;
	for(int i = 2; i <= n; i++) {
		if(a[i] > a[i - 1]) {
			cnt++;
			ans = std::max(ans, cnt);
		}else cnt = 1;
	}
	printf("%d\n", ans);
	return 0;
}
