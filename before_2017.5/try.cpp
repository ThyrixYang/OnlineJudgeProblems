#include <bits/stdc++.h>

#define pow dddddsdf
long long pow(long long x, long long p) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1)  ans = ans * x;
		x = x * x;
		p >>= 1;
	}
	return ans;
}
int cnt[100];
int K = 3;
long long f(int y) {
	long long ans = 0;
	int p = y;
	while(y > 0) {
		ans += pow(y % 10, K);
		y /= 10;
	}
	ans -= p;
	return ans;
}
int main() {
	for(int i = 0; i < 100000; i++) {
		int e = f(i);
		if(e >= 0 && e < 100) cnt[e]++;
	}
	for(int i = 0; i < 100; i++) {
		printf("%d %d\n", i, cnt[i]);
	}
	return 0;
}
