#include <bits/stdc++.h>

using namespace std;
int T, cas = 0;
int cnt[10];
int use[60][3];
int ans;
int tcnt; 
void dfs(int p, int c) {
	//printf("%d %d\n", p, c);
	if(tcnt - p + c <= ans) return;
	if(p == tcnt) {
		ans = max(ans, c);
		return;
	}
	int f = 1;
	for(int i = 0; i < 3; i++) {
		cnt[use[p][i]]--;
		if(cnt[use[p][i]] < 0) f = 0;
	}
	if(f) {
		dfs(p + 1, c + 1);
	}
	for(int i = 0; i < 3; i++) {
		cnt[use[p][i]]++;
	}
	dfs(p + 1, c);
}
int main() {
	freopen("./in", "r", stdin);
	int t = 0;
	for(int i = 1; i <= 9; i++) {
		for(int j = 1; j <= 9; j++) {
			int k = i - j;
			if(k <= 0) continue;
			if(k > 9) continue;
			if(k < j) continue;
			use[t][0] = j, use[t][1] = k, use[t][2] = i;
			t++;
			if(j != k) {
				use[t][0] = k, use[t][1] = j, use[t][2] = i;
				t++;
			}
		}
	}
	tcnt = t;
	std::cin >> T;
	while(T--) {
		for(int i = 1; i < 10; i++) {
			scanf("%d", &cnt[i]);
		}
		printf("Case #%d: ", ++cas);
		ans = 0;
		dfs(0, 0);
		printf("%d\n", ans);
	}
	return 0;
}
