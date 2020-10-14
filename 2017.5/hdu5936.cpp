#include <bits/stdc++.h>

int T, cas = 0;
int X, K;
int cnt[10];
int tmp[10];
long long pp[10][20];
bool check(long long x) {
	if(x < 0) return 0;
	std::memset(tmp, 0, sizeof tmp);
	while(x > 0) {
		int d = x % 10;
		tmp[d]++;
		if(d != 0 && tmp[d] > cnt[d]) return 0;
		x /= 10;
	}
	for(int i = 1; i < 10; i++) {
		if(tmp[i] != cnt[i]) {
			return 0;
		}
	}
	return 1;
}
int ans;
void dfs(int p, int d) {
	if(p == 11) {
		long long f = 0;
		for(int i = 1; i < 10; i++) {
			f += cnt[i] * pp[i][K];
		}
		if(f != 0 && check(f - X)) {
			ans++;
		}
		return;
	}
	for(int i = d; i < 10; i++) {
		cnt[i]++;
		dfs(p + 1, i);
		cnt[i]--;
	}
}
int main() {
	freopen("./in", "r", stdin);
	for(int i = 0; i < 10; i++) {
		pp[i][0] = 1;
		for(int j = 1; j < 20; j++) {
			pp[i][j] = pp[i][j - 1] * i;
		}
	}
	std::cin >> T;
	while(T--) {
		scanf("%d%d", &X, &K);
		printf("Case #%d: ", ++cas);
		ans = 0;
		dfs(0, 0);
		printf("%d\n", ans);
	}
	return 0;
}
