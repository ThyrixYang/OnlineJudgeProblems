#include <bits/stdc++.h>

const int MAXN = 2e5;
int n, m;
int len1[MAXN], len2[MAXN];
int a[MAXN], b[MAXN];
int main() {
	freopen("./in", "r", stdin);
	std::cin >> n >> m;
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	for(int i = 0; i < m; i++) scanf("%d", &b[i]);
	for(int i = 0, j = -1; i < n; i++) {
		while(j + 1 < m && b[j + 1] <= a[i]) j++;
		if(j == -1) len1[i] = 2e9;
		else len1[i] = std::abs(b[j] - a[i]);
	}
	int ans = 0;
	for(int i = n - 1, j = m; i >= 0; i--) {
		while(j > 0 && b[j - 1] >= a[i]) j--;
		if(j < m) 
		len2[i] = std::abs(b[j] - a[i]);
		else len2[i] = 2e9;
		ans = std::max(ans, std::min(len1[i], len2[i]));
	}
	printf("%d\n", ans);
	return 0;
}
