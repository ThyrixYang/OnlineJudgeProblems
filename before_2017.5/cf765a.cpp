#include <bits/stdc++.h>

using namespace std;

char home[10];
char s[20];
int main() {
	int N;
	cin >> N;
	scanf("%s", home);
	int cnt = 0;
	for(int i = 0; i < N; i++) {
		scanf("%s", s);
		int ok = 1;
		for(int j = 0; j < 3; j++) {
			if(s[j] != home[j]) {
				ok = 0;
				break;
			}
		}
		if(ok == 1) cnt++;
		else cnt--;
	}
	if(cnt > 0) puts("contest");
	else puts("home");
	return 0;
}
