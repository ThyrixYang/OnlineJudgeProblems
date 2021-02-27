#include <bits/stdc++.h>

using namespace std;

char s[1000];
int cnt[100];
int main() {
	scanf("%s", s);
	int len = strlen(s);
	int ans = 1;
	for(int i = 0; i < len; i++) {
		if(s[i] == 'a') cnt[0]++;
		else if(cnt[s[i] - 'a' - 1] == 0) {
			ans = 0;
			break;
		} else {
			cnt[s[i] - 'a']++;
		}
	}
	if(ans) puts("YES");
	else puts("NO");
	return 0;
}
