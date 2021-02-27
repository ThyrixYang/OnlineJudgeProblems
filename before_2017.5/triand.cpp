#include <bits/stdc++.h>

const int MAXN = 1e7;
char s[MAXN];
char in[MAXN];
int n;
const long long up = 1e5;
int stk[MAXN], top;
int match[MAXN];
long long cal1(int l, int r) {
	long long ans = 1;
	for(int i = l; i <= r; i++) {
		if(s[i] == '|') ans++;
	}
	return ans;
}
long long cal2(int l, int r) {
	long long ans = 1;
	long long g = 1;
	for(int i = l; i <= r; i++) {
		if(s[i] != ' ') {
			ans *= g;
			g = 1;
			if(ans > up) return -1;
		}
		else {
			g++;
		}
	}
	ans *= g;
	if(ans > up) return -1;
	return ans;
}
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d", &n) != EOF) {
		top = 0;
		gets(in);
		int len = 0;
		s[0] = 0;
		for(int i = 0; i < n; i++) {
			gets(in);
			int l = strlen(in);
			for(int j = 0; j < l; j++) {
				s[len++] = in[j];
			}
			s[len] = 0;
		}
		for(int i = 0; i < len; i++) {
			if(s[i] == '{') {
				stk[top++] = i;
			}
			else if(s[i] == '}') {
				int x = stk[--top];
				match[i] = x;
				match[x] = i;
			}
			else if(s[i] == '$') {
				if(top > 0 && s[stk[top - 1]] == '$') {
					int x = stk[--top];
					match[i] = x;
					match[x] = i;
				}
				else stk[top++] = i;
			}
		}
		long long ans = 1;
		for(int i = 0; i < len; i++) {
			if(s[i] == '{') {
				int r = match[i];
				ans *= cal1(i + 1, r - 1);
				if(ans < 0 || ans > up) {
					ans = -1;
					break;
				}
				i = r;
			}
			if(s[i] == '$') {
				int r = match[i];
				ans *= cal2(i + 1, r - 1);
				if(ans < 0 || ans > up) {
					ans = -1;
					break;
				}
				i = r;
			}
		}
		if(ans > 0) printf("%lld\n", ans);
		else puts("doge");
	}
	return 0;
}
