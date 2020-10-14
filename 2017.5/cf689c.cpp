#include <bits/stdc++.h>

unsigned long long m, n, l, r, mid, k, cnt, x;
int main() {
	std::cin >> m;
	l = 1, r = 1e18;
	while(r - l > 1) {
		mid = (r + l) >> 1;
		cnt = 0;
		for(k = 2; (x = k * k * k) <= mid; k++) {
			cnt += mid / x;
			if(cnt > m) break;
		}
		if(cnt >= m) r = mid;
		else l = mid;
	}
	cnt = 0;
	for(k = 2; (x = k * k * k) <= r; k++) {
		cnt += r / x;
		if(cnt > m) break;
	}
	if(cnt == m) std::cout << r;
	else puts("-1");

	return 0;
}
