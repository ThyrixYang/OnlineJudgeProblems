#include <bits/stdc++.h>

const int MAXN=1e7+30000;
int phi[MAXN];
int pri[MAXN];
long long sum[MAXN];
bool VIS[MAXN];
const long long MOD = 1e9 + 7;
void getEular(){
	phi[1] = 1;
	for(int i=2;i<MAXN;i++){
		if(!VIS[i]) pri[++pri[0]]=i,phi[i]=i-1;
		for(int j=1;j<=pri[0]&&i*pri[j]<MAXN;j++){
			VIS[i*pri[j]]=1;
			if(i%pri[j]==0){
				phi[i*pri[j]]=phi[i]*pri[j];
				break;
			}else{
				phi[i*pri[j]]=phi[i]*(pri[j]-1);
			}
		}
	}
	for(int i = 1; i < MAXN; i++) sum[i] = (sum[i - 1] + phi[i]) % MOD;
}
long long getk(int n, int m) {
	if(n == 1) return sum[m] % MOD;
	if(m == 1) return phi[n] % MOD;
	if(m == 0) return 0;
	for(int pos = 1;;pos++) {
		if(n % pri[pos] == 0) {
			return (getk(n / pri[pos], m) * (long long)phi[pri[pos]] % MOD + getk(n, m / pri[pos])) % MOD;
		}
	}
}
long long qpow(long long a, long long p, long long mod) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % mod;
		a = a * a % mod;
		p >>= 1;
	}
	return ans ;
}
int n, m, p;
long long getAns(long long k, long long p) {
	if(p == 1) return 0;
	long long x = getAns(k, phi[p]);
	return qpow(k, phi[p] + x, p);
}
int main() {
	getEular();
	while(scanf("%d%d%d", &n, &m, &p) != EOF) {
		int k = getk(n, m);
		printf("%lld\n", getAns(k, p));
	}
	return 0;
}
