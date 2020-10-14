#include <bits/stdc++.h>

const int MAXN = 1e5 + 300;
int M, N;
char s[MAXN];
int vis[MAXN];
int check(char c) {
	std::memset(vis, 0, sizeof vis);
	int pos = -1;
	for(;;) {
		int f = 1;
		while(f) {
			f = 0;
			for(int i = pos + 1; i <= pos + M && i < N; i++) {
				if(s[i] < c) {
					pos = i;
					f = 1;
					break;
				}
			}
		}
		if(pos + M - 1>= N - 1) return 1;
		int last = -1;
		for(int i = pos + 1; i <= pos + M && i < N; i++) {
			if(s[i] == c) last = i;
		}
		if(last == -1) return 0;
		vis[last] = 1;
		pos = last;
	}
}
char res[MAXN];
int rh;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> M;
	scanf("%s", s);
	N = strlen(s);
	char x = 'a';
	for(;;) {
		if(check(x)) {
			break;
		}
		x++;
	}
	for(int i = 0; i < N; i++) {
		if(s[i] < x) res[rh++] = s[i];
		if(vis[i]) res[rh++] = s[i];
	}
	char mm = 'z';
	if(rh == 0) {
		for(int i = 0; i < N; i++) {
			mm = std::min(mm, s[i]);
		}
		res[rh++] = mm;
	}
	std::sort(res, res + rh);
	puts(res);
	return 0;
}
