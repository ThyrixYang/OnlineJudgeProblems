#include <bits/stdc++.h>

using namespace std;
const int MAXN = 1e6;
int N;
long long d[MAXN], dh;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N;
	long long res = 0;
	for(int i = 0; i < N; i++) {
		long long a0, b0, a1, b1;
		scanf("%lld%lld%lld%lld", &a0, &b0, &a1, &b1);
		a0 *= 2;
		a1 *= 2;
		b0 *= 2;
		b1 *= 2;
		if(a0 + b0 >= a1 + b1) {
			d[dh++] = (a0 + b0) / 2;
			d[dh++] = (a1 + b1) / 2;
			res += (a0 - b0 + a1 - b1) / 2;
		} else if(a0 > b1) {
			res += (a0 - b1);
		} else if(b0 > a1) {
			res += (a1 - b0);
		}
	}
	std::sort(d, d + dh, greater<long long>() );
	for(int i = 0; i < dh; i++) {
		if(i & 1) res -= d[i];
		else res += d[i];
	}
	std::cout << res / 2 << std::endl;
	return 0;
}
