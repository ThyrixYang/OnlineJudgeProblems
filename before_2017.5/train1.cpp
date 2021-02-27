#include <bits/stdc++.h>

int n;
int a[MAXN];
int tol = 0;
int main() {
	std::cin >> n;
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	std::sort(a, a + n);
	int h = 0;
	for(; h < n; h++) {
		if(tol + a[h] > 710) break;
		tol += a[h];
	}
	int ansp = 0;
	int ansd = 1e9;
	for(int i = 10; i <= 360; i++) {

	}
	return 0;
}
