#include <bits/stdc++.h>

const int MAXN = 1e6;
char s[MAXN];
char t[MAXN];
int a, b;
int bk[MAXN];
int p[MAXN];
int main() {
	freopen("./in", "r", stdin);
	while(gets(s)) {
		scanf("%d%d", &a, &b);
		gets(t);
		int len = strlen(s);
		for(int i = 0; i < len; i++) {
			int j = i;
			while(j < len && islower(s[j])) j++;
			bk[i] = j;
			i = j;
		}
		for(int i = 0; i < len; i++) p[i] = 0;
		for(int i = a; i <= b; i++) {
			int ans = 0;
			for(int j = 0; j < len; j++) {
				ans += bk[p[j]] - p[j] + 1;
				if(bk[p[j]] == len) break;
				p[j + 1] = std::max(p[j + 1], bk[p[j]] + 1);
				while(bk[p[j + 1]] < len && bk[p[j + 1]] - p[j] <= i) {
					p[j + 1] = bk[p[j + 1]] + 1;
				}
				if(bk[p[j + 1]] == len && len - p[j] <= i) {
					break;
				}
			}
			//printf("%d\n", ans - 1);
		}
	}
	return 0;
}
