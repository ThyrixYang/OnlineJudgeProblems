#include <bits/stdc++.h>

using namespace std;
const long long MOD = 1e9 + 7;
long long qpow(long long a, long long p) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
long long N, K;
int maxn;
struct Matrix{
	long long a[100][100];
	Matrix(){memset(a,0,sizeof a);}
	Matrix operator * (Matrix b){
		Matrix ans;
		for(int i=0;i<maxn;i++)
			for(int j=0;j<maxn;j++) {
				for(int k=0;k<maxn;k++)
					ans.a[i][j] += a[i][k] * b.a[k][j] % MOD;
				ans.a[i][j] %= MOD;
			}
		return ans;
	}
};
Matrix qpow(Matrix a,long long p){
	Matrix ans;
	for(int i=0;i<maxn;i++) ans.a[i][i]=1;
	while(p>0){
		if(p&1) ans=ans*a;
		a=a*a;p>>=1;
	}
	return ans;
}
long long fac[100], inv[100];
void ma(long long &a, long long b) {
	a += b;
	if(a < 0) a += MOD;
	if(a >= MOD) a -= MOD;
}
long long C(int n, int k) {
	return fac[n] * inv[k] % MOD * inv[n - k] % MOD;
}
int main() {
	freopen("./in", "r", stdin);
	fac[0] = inv[0] = 1;
	for(int i = 1; i < 100; i++) {
		fac[i] = fac[i - 1] * i % MOD;
		inv[i] = qpow(fac[i], MOD - 2);
	}
	std::cin >> N >> K;
	maxn = (K + 1) * 2 + 1;
	Matrix t;
	for(int i = K + 1; i <= K * 2 + 1; i++) {
		for(int j = i - K - 1; j <= K; j++) {
			long long cc = C(K * 2 + 1 - i, j + K + 1 - i);
			ma(t.a[i][j], cc);
			ma(t.a[i - K - 1][j], cc);
		}
	}
	for(int i = 0; i <= K; i++) {
		for(int j = i + K + 1; j <= K * 2 + 1; j++) {
			long long cc = C(K - i, j - i - K - 1);
			ma(t.a[i][j], cc);
		}
	}
	ma(t.a[(K + 1) * 2][0], 1);
	ma(t.a[(K + 1) * 2][K + 1], 1);
	ma(t.a[(K + 1) * 2][(K + 1) * 2], 1);
	Matrix res = qpow(t, N);
	long long ans = 0;
	for(int i = 0; i <= K; i++) {
		ma(ans, res.a[(K + 1) * 2][i]);
	}
	std::cout << ans << std::endl;
	return 0;
}
