#include <bits/stdc++.h>

char s[200];
int r, c;
int main() {
	std::cin >> r >> c;
	for(int i = 0; i < r; i++) {
		scanf("%s", s);
	}
	int cnt = 0;
	int a = 0;
	for(int i = 0; i < c; i++) {
		if(s[i] == 'B'){
			if(a == 0) cnt++;
			a = 1;
		}else a = 0;
	}
	std::cout << cnt;
	return 0;
}
