#include <bits/stdc++.h>

int k;
int a[20];
int main() {
	freopen("./in", "r", stdin);
	std::cin >> k;
	for(int i = 0; i < 12; i++) {
		scanf("%d", &a[i]);
	}
	std::sort(a, a + 12);
	std::reverse(a,  a + 12);
	int sum  = 0;
	int ans = -1;
	for(int i = 0; i < 12; i++) {
		if(sum >= k) {
			ans = i;
			break;
		}
		sum += a[i];
	}
	if(sum >= k && ans == -1) ans = 12;
	printf("%d\n", ans);
	return 0;
}
