#include <bits/stdc++.h>

int d; 
int a[5];
int ans = 0;
int lcm(int x, int y) {
	return x * y / std::__gcd(x, y);
}
void dfs(int p, int val, int f) {
	if(p == 4) {
		if(f == 2) return;
		ans += d / val * f;
		return;
	}
	if(f == 2) {
		dfs(p + 1, lcm(val , a[p]), 1);
		dfs(p + 1, val, 2);
	}else {
		dfs(p + 1, lcm(val , a[p]), -f);
		dfs(p + 1, val, f);
	}
}
int main() {
	freopen("./in", "r", stdin);
	for(int i = 0; i < 4; i++) scanf("%d", &a[i]);
	scanf("%d", &d);
	dfs(0, 1, 2);
	printf("%d\n", ans);
	return 0;
}
