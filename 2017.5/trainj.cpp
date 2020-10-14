#include <bits/stdc++.h>

const int MAXN = 2e6;
char s[MAXN];
int n;
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%s", s) != EOF) {
		n = strlen(s);
		int c1 = 0, c2 = 0;
		int cx = 0;
		for(int i = 0; i < n; i++) {
			if(s[i] == '(') c1++;
			if(s[i] == ')') {
				c1--;
				if(c1 < 0) break;
			}
			if(s[i] == '?') {
				c1++;
				cx++;
			}
		}
		for(int i = n - 1; i >= 0; i--) {
			if(s[i] == ')') c2++;
			if(s[i] == '(') {
				c2--;
				if(c2 < 0) break;
			}
			if(s[i] == '?') {
				c2++;
			}
		}
		if(c1 < 0 || c2 < 0) puts("None");
		else if(c1 == 0 || c2 == 0) {
			puts("Unique");
		}else {
			int x = std::min(c1, c2);
			if(x % 2 == 0 && cx * 2 >= x) puts("Many");
			else puts("None");
		}
	}
	return 0;
}
