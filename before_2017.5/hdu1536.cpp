#include <bits/stdc++.h>

const int MAXN = 1e4 + 300;
int K, M;
int s[MAXN];
int sg[MAXN];
int vis[MAXN], tm;
int main() {
	freopen("in", "r", stdin);
	while(scanf("%d", &K), K) {
		for(int i = 0; i < K; i++) {
			scanf("%d", &s[i]);
		}
		std::sort(s, s + K);
		for(int i = 1; i < MAXN; i++) { 
			tm++;
			for(int j = 0; j < K; j++) {
				if(i - s[j] < 0) break;
				vis[sg[i - s[j]]] = tm;
			}
			for(int j = 0;;j++) {
				if(vis[j] != tm) {
				 	sg[i] = j;
				 	break;
				}
			}
		}
		scanf("%d", &M);
		while(M--) {
			int l;
			scanf("%d", &l);
			int res = 0;
			for(int i = 0; i < l; i++) {
				int x;
				scanf("%d", &x);
				res ^= sg[x];
			}
			if(res) printf("W");
			else printf("L");
		}
		puts("");
	}
	return 0;
}