#include <bits/stdc++.h>

long long a00, a01, a10, a11;
long long cal1(long long x) {
	if(x == 0) return 0;
	for(long long d = 2; d * (d - 1) <= 2 * x; d++) {
		if(d * (d - 1) == 2 * x) return d;
	}
	return -1;
}
const int MAXN = 1e6 + 30000;
int A[MAXN], ah;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> a00 >> a01 >> a10 >> a11;
	if(a00 == 0 && a01 == 0 && a10 == 0 && a11 == 0) {
		puts("0");
		return 0;
	}
	long long c0 = cal1(a00);
	long long c1 = cal1(a11);
	if(c0 == -1 || c1 == -1) {
		puts("Impossible");
		return 0;
	}
	if(c0 == 0 && (a01 || a10)) c0 = 1;
	if(c1 == 0 && (a10 || a01)) c1 = 1;
	if(c0 * c1 != a10 + a01) {
		puts("Impossible");
		return 0;
	}
	int f = 1;
	while(c1 + c0 > 0) {
		if((c0 <= a10 && c1) && (c1 <= a01 && c0)) {
			if(a10 > a01) {
				A[ah++] = 1;
				c1--;
				a10 -= c0;
			} else {
				A[ah++] = 0;
				c0--;
				a01 -= c1;
			}
		} else if(c0 <= a10 && c1) {
			A[ah++] = 1;
			c1--;
			a10 -= c0;
		} else if(c1 <= a01 && c0) {
			A[ah++] = 0;
			c0--;
			a01 -= c1;
		} else {
			f = 0;
			break;
		}
	}
	if(a10 > 0 || a01 > 0 || c1 > 0 || c0 > 0) f = 0;
	if(!f) puts("Impossible");
	else {
		for(int i = 0 ; i < ah; i++) {
			printf("%d", A[i]);
		}
	}
	return 0;
}
