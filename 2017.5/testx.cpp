#include <bits/stdc++.h>

const int MAXN = 1e6;
int a[MAXN][20];
int h;
int v[20];
void dfs(int p, int s) {
	if(p == 10) {
		std::memcpy(a[h], v, sizeof v);
		h++;
		return;
	}
	for(int i = s; i <= 9; i++) {
		v[p] = i;
		dfs(p + 1, i);
	}
}
int main() {
	freopen("in.txt", "r", stdin);
	dfs(0, 0);
	std::cout << h << std::endl;
	return 0;
}
