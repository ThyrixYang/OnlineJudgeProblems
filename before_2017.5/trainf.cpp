#include <bits/stdc++.h>

const int MAXN = 2000;
int T;
int n;
char s[MAXN];
int a[MAXN], b[MAXN];
int l[MAXN], r[MAXN];
int cas = 0;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		scanf("%s", s);
		n = strlen(s);
		std::memset(a, -1, sizeof a);
		std::memset(b, -1, sizeof b);
		for(int i = 0; i < n; i++) {
			l[i] = a[s[i]];
			a[s[i]] = i;
		}
		for(int i = n - 1; i >= 0; i--) {
			r[i] = b[s[i]];
			b[s[i]] = i;
		}
		int ans = -1;
		for(int i = 0; i < n; i++) {
			if(l[i] != -1) {
				if(ans == -1) ans = i - l[i];
				else ans = std::min(ans, i - l[i]);
			}
			if(r[i] != -1) {
				if(ans == -1) ans = r[i] - i;
				else ans = std::min(ans, r[i] - i);
			}
		}
		printf("Case #%d: %d\n", ++cas, ans);
	}
	return 0;
}
