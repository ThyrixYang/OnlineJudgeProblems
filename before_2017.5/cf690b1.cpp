#include <bits/stdc++.h>

char B[54][54];
char A[54][54];
int n;
bool check(int x1, int y1, int x2,int y2) {
	memset(A, '0', sizeof A);
	for(int i = 1; i <= n; i++) A[i][n + 1] = 0;
	for(int i = x1; i < x2; i++) {
		for(int j = y1; j < y2; j++) {
			A[i][j] = '4';
		}
	}
	if(x1 - 1 >= 1) {
		for(int i = y1; i < y2; i++) A[x1 - 1][i] = '2';
		if(y1 - 1 >= 1) A[x1 - 1][y1 - 1] = '1';
		if(y2 <= n) A[x1 - 1][y2] = '1';
	}
	if(x2 <= n) {
		for(int i = y1; i < y2; i++) A[x2][i] = '2';
		if(y1 - 1>= 1) A[x2][y1 - 1] = '1';
		if(y2 <= n) A[x2][y2] = '1';
	}
	if(y1 - 1 >= 1) {
		for(int i = x1; i < x2; i++) A[i][y1 - 1] = '2';
	}
	if(y2 <= n) {
		for(int i = x1; i < x2; i++) A[i][y2] = '2';
	}
	for(int i = 1; i <= n; i++) {
		if(memcmp(A[i] + 1, B[i] + 1, sizeof(char) * n) != 0) return 0;

	}
	return 1;
}
int main() {
	std::cin >> n;
	for(int i = 1; i <= n; i++) {
		scanf("%s", B[i] + 1);
	}
	for(int x = 1; x <= n; x++) {
		for(int y = 1; y <= n; y++) {
			for(int x2 = x + 1; x2 <= n + 1; x2++) {
				for(int y2 = y + 1; y2 <= n + 1; y2++) {
					if(check(x, y, x2, y2)) {
						puts("Yes");
						return 0;
					}
				}
			}
		}
	}
	puts("No");
	return 0;
}
