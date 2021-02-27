#include <bits/stdc++.h>

const int MAXN = 1e6 + 3000;
int cas;
int q;
short cnt[MAXN][23];
short vis[MAXN][23], tm;
char s[20];
int dis[MAXN];
int notp[MAXN];
int pri[MAXN];
int main() {
	dis[1] = 0;
	for(int i = 2; i < MAXN; i++) {
		if(!notp[i]) pri[++pri[0]] = i;
		for(int j = 1; j <= pri[0]; j++) {
			int x = pri[j];
			if(x * i >= MAXN) break;
			notp[x * i] = 1;
			if(i % x == 0) break;
		}
	}
	for(int i = 1; i < MAXN; i++) {
		for(int j = 1; j <= pri[0]; j++) {
			int x = pri[j];
			if(x * i >= MAXN) break;
			dis[x * i] = dis[i] + 1;
		}
	}
	freopen("./in", "r", stdin);
	while(scanf("%d", &q)) {
		if(q == 0) break;
		std::set<int> S;
		printf("Case #%d:\n", ++cas);
		tm++;
		while(q--) {
			int x;
			scanf("%s", s);
			scanf("%d", &x);
			if(s[0] == 'I') {
				if(S.find(x) != S.end()) continue;
				S.insert(x);
				for(int d = 1; d * d <= x; d++) {
					if(x % d == 0) {
						int y = dis[x / d];
						if(vis[d][y] != tm) vis[d][y] = tm, cnt[d][y] = 0;
						++cnt[d][y];
						if(d * d != x) {
							int v = x / d;
							int y = dis[d];
							if(vis[v][y] != tm) vis[v][y] = tm,
								cnt[v][y] = 0;
							++cnt[v][y];
						}
					}
				}
			} else if(s[0] == 'D') {
				if(S.find(x) == S.end()) continue;
				S.erase(x);
				for(int d = 1; d * d <= x; d++) {
					if(x % d == 0) {
						int y = dis[x / d];
						if(vis[d][y] != tm) vis[d][y] = tm, cnt[d][y] = 0;
						--cnt[d][y];
						if(d * d != x) {
							int v = x / d;
							int y = dis[d];
							if(vis[v][y] != tm) vis[v][y] = tm,
								cnt[v][y] = 0;
							--cnt[v][y];
						}
					}
				}
			} else {
				int ans = 1e9;
				for(int d = 1; d * d <= x; d++) {
					if(x % d == 0) {
						int y = dis[x / d];
						for(int j = 0; j < 23; j++) {
							if(vis[d][j] == tm && cnt[d][j] != 0) {
								ans = std::min(ans, j + y);
								break;
							}
						}
						if(d * d != x) {
							int v = x / d;
							int y = dis[d];
							for(int j = 0; j < 23; j++) {
								if(vis[v][j] == tm && cnt[v][j] != 0) {
									ans = std::min(ans, y + j);
									break;
								}
							}
						}
					}
				}
				if(ans > 1e8) ans = -1;
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}
