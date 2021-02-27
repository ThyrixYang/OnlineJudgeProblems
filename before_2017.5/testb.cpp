#include <bits/stdc++.h>

long long MOD;
struct Mat {
	long long a[2][2];
	Mat(){std::memset(a, 0, sizeof a);}
	Mat operator * (const Mat &A) const {
		Mat ans;
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 2; j++) {
				for(int k = 0; k < 2; k++) {
					ans.a[i][j] += a[i][k] * A.a[k][j] % MOD;
				}
				ans.a[i][j] %= MOD;
			}
		}
		return ans;
	}
};
Mat qpow(Mat t, long long p) {
	Mat res;
	res.a[0][0] = res.a[1][1] = 1;
	while(p > 0) {
		if(p & 1) res = res * t;
		t = t * t;
		p >>= 1;
	}
	return res;
}
int T, N;
const int mod = 26880696;
int main() {
	freopen("in.txt", "r", stdin);
	std::cin >> T;
	while(T--) {
		scanf("%d", &N);
		Mat t;
		t.a[0][0] = t.a[0][1] = t.a[1][0] = 1;
		MOD = mod;
		Mat res = qpow(t, N);
		int p1 = res.a[1][0];
		MOD = 20160519;
		int ans = qpow(t, p1).a[1][0];
		printf("%d\n", ans);
	}
	return 0;
}
