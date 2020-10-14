#include <bits/stdc++.h>
const int MAXN = 1e6 + 300;
char s[MAXN];
char sh(char c) {
	if(c != 'a') return c - 1;
	else return 'z';
}
int main() {
	freopen("./in", "r", stdin);
	scanf("%s", s);
	int len = strlen(s);
	int st = -1, ed = -1;
	for(int i = 0; i < len; i++) {
		if(s[i] != 'a' && st == -1) {
			st = i;
		} 
		if(s[i] == 'a' && st != -1) {
			break;
		}
		if(st != -1) ed = i;
	}
	if(st == -1) st = ed = len - 1;
	for(int i = 0; i < len; i++) {
		if(i >= st && i <= ed) printf("%c", sh(s[i]));
		else printf("%c", s[i]);
	}
	return 0;
}
