#include <bits/stdc++.h>

const int MAXN = 1e6;
char s[MAXN];
int n;
int len;
int main() {
	freopen("./in", "r", stdin);
	scanf("%d%d", &len, &n);
	scanf("%s", s);
	int lastr = len - 1;
	int p = -1;
	for(int i = 0; i < len; i++) {
		if(s[i] == '.') {
			p = i;
			break;
		}
	}
	for(int i = len - 1; i > p; i--) {
		if(s[i] >= '5') {
			if(s[i - 1] >= '5' && s[i] != '.') continue;
			int cnt = 1;
			int j = i - 1;
			if(s[j] == '.') {
				j--;
				lastr = j;
				break;
			}
			lastr = j;
			while(j > 0 && (s[j] + 1 == '5' && cnt < n)) {
				j--;
				if(s[j] == '.') {
					j--;
					break;
				}
				cnt++;
				lastr = std::min(lastr, j);
			}
			lastr = j;
			i = j + 1;
		}
	}
	int fs = 0;
	if(lastr < len - 1) {
		int i = lastr;
		s[i]++;
		while(i > 0 && (s[i] == '9' + 1 || s[i] == '.')) {
			if(s[i] == '.') {
				i--;
				continue;
			}
			s[i] = '0';
			s[i - 1]++;
			lastr = i - 1;
			i--;
		}
		if(i == 0 && s[0] == '9' + 1) {
			fs = 1;
			s[0] = '0';
		}
	}
	if(fs) printf("1");
	for(int i = 0; i <= lastr; i++) printf("%c", s[i]);
	for(int i = lastr + 1; i < p; i++) printf("0");
	return 0;
}
