#include <bits/stdc++.h>

const int MAXN = 20000;
int N;
char s[MAXN];
int a[MAXN], ah;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N;
	scanf("%s", s);
	int cnt = 0;
	for(int i = 0; i < N; i++) {
		if(s[i] == 'W') {
			if(cnt) {
				a[ah++] = cnt;
				cnt = 0;
			}
			continue;
		}
		else {
			cnt++;
		}
	}
	if(cnt > 0) a[ah++] = cnt;
	std::cout << ah << std::endl;
	for(int i = 0; i < ah; i++) printf("%d ", a[i]);
	return 0;
}
