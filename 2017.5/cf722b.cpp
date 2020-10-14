#include <bits/stdc++.h>

const int MAXN = 1005;
int N;
int a[MAXN];
char s[MAXN];
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N;
	for(int i = 0; i < N; i++) scanf("%d", &a[i]);
	gets(s);
	int f = 1;
	for(int i = 0; i < N; i++) {
		gets(s);
		int len = strlen(s);
		int cnt = 0;
		for(int j = 0; j < len; j++) {
			if(s[j] == 'a' || s[j] == 'e' || s[j] == 'i' || s[j] == 'o'
				||	s[j] == 'u' || s[j] == 'y') cnt++;
		}
		if(cnt != a[i]) {
			f = 0;
		}
	}
	if(f) puts("YES");
	else puts("NO");
	return 0;
}
