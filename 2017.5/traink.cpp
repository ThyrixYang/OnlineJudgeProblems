#include <bits/stdc++.h>

const int MAXN = 2e5;
int T;
int n;
char s[MAXN];
long long a[MAXN], ah;
#define sq(x) ((x) * (x))
int cas;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		scanf("%s", s);
		n = strlen(s);
		ah = 1;
		int cnt = 1;
		long long res = 0;
		for(int i = 1; i < n; i++) {
			if(s[i] != s[i - 1]) {
				a[ah++] = cnt;
				cnt = 1;
			}else cnt++;
		}
		a[ah++] = cnt;
		for(int i = 1; i < ah; i++) {
			res += sq(a[i]);
		}
		a[ah] = 0;
		long long ans = res;
		for(int i = 1; i < ah; i++) {
			if(a[i] == 1) {
				ans = std::max(ans, res - sq(a[i - 1]) -
						sq(a[i]) - sq(a[i + 1])+ sq(a[i - 1] + a[i] + a[i + 1]));
			}
			else{
				ans = std::max(ans, res - sq(a[i - 1]) - sq(a[i]) + sq(a[i - 1] + 1)
					+sq(a[i] - 1));
				ans = std::max(ans, res - sq(a[i + 1]) - sq(a[i]) +sq(a[i + 1] + 1)
						+ sq(a[i] - 1));
			}

		}
		printf("Case #%d: %lld\n", ++cas, ans);
	}
	return 0;
}
