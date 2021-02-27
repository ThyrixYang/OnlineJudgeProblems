#include <bits/stdc++.h>

char s[100];
int len = 27;
int pos[2000];
char out[2][222];
int x = 0, y = 0;
int nt() {
	
}
int main() {
	scanf("%s", s);
	std::memset(pos, -1, sizeof pos);
	int p[2];
	for(int i = 0; i < len; i++) {
		if(pos[s[i]] != -1) {
			p[0] = pos[s[i]];
			p[1] = i;
		}
		pos[s[i]] = i;
	}
	if(p[1] - p[0] == 1) {
		puts("Impossible");
	} else {
		
	}
	return 0;
}
