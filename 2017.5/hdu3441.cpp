#include <bits/stdc++.h>

//判定N是否是素数，若不是，输出N的最小因子
typedef long long ll;
using namespace std;
//求a，b的最大公约数
ll gcd(ll a,ll b){
    if(b==0) return a;
    return gcd(b,a%b);
}
//求a*b%c,因为a，b很大，所以要先将b写成二进制数，再加：例如3*7=3*(1+2+4);
//注意直接乘会爆ll
ll mulmod(ll a,ll b,ll c){
    ll cnt=0,temp=a;
    while(b){
        if(b&1) cnt=(cnt+temp)%c;
        temp=(temp+temp)%c;
        b>>=1;
    }
    return cnt;
}
//求a^b%c,再次将b写成二进制形式，例如：3^7=3^1*3^2*3^4;
ll powmod(ll a,ll b,ll c){
    ll cnt=1,temp=a;
    while(b){
        if(b&1) cnt=mulmod(cnt,temp,c);//cnt=(cnt*temp)%c;
        temp=mulmod(temp,temp,c);//temp=(temp*temp)%c;
        b>>=1;
    }
    return cnt;
}
//Miller-Rabin测试n是否为素数,1表示为素数，0表示非素数
const int testsize=5;
int pri[10]={2,3,5,7,11,13,17,19,23,29};//素数表可以适当减小
bool Miller_Rabin(ll n){
    if(n<2) return 0;
    if(n==2) return 1;
    if(!(n&1)) return 0;
    ll k=0,m;
    m=n-1;
    while(m%2==0) m>>=1,k++;//n-1=m*2^k
    for(int i=0;i<testsize;i++){
        if(pri[i]>=n) return 1;
        ll a=powmod(pri[i],m,n);
        if(a==1) continue;
        int j;
        for(j=0;j<k;j++){
            if(a==n-1) break;
            a=mulmod(a,a,n);
        }
        if(j<k) continue;
        return 0;
    }
    return 1;
}
//pollard_rho 大整数分解，给出n的一个非1因子，返回n是为一次没有找到
ll pollard_rho(ll C,ll N){
    ll I, X, Y, K, D;
    I = 1;
    X = rand() % N;
    Y = X;
    K = 2;
    do{
        I++;
        D = gcd(N + Y - X, N);
        if (D > 1 && D < N) return D;
        if (I == K) Y = X, K *= 2;
        X = (mulmod(X, X, N) + N - C) % N;
    }while (Y != X);
    return N;
}
//找出N的最小质因数
ll rho(ll N){
	if(N == 1) return 1;
    if (Miller_Rabin(N)) return N;
    do{
        ll T = pollard_rho(rand() % (N - 1) + 1, N);
        if (T < N){
              ll A, B;
              A = rho(T);
              B = rho(N / T);
              return A < B ? A : B;
        }
    }
    while(1);
}
struct Node {
	long long p;
	int cnt;
	Node(long long p = 0, int cnt = 0): p(p), cnt(cnt) {}
	bool operator < (const Node &C) const {
		return p < C.p;
	}
};
const int MAXN = 1e6;
Node dv[MAXN];
int dvh = 0;
long long dd[MAXN], ddh = 0;
void getd(long long x) {
	dvh = 0;
	long long d;
	while(x > 1 && ((d = rho(x)) != x)) {
		int cnt = 0;
		while(x % d == 0) {
			x /= d;
			cnt++;
		}
		dv[dvh++] = Node(d, cnt);
	}
	if(x > 1) dv[dvh++] = Node(x, 1);
	sort(dv, dv + dvh);
}
const long long MOD = 1e9 + 7;
long long qpow(long long a, long long p) {
	a %= MOD;
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
long long inv(long long x) {
	return qpow(x, MOD - 2);
}
int T, cas = 0;
long long A, C;
long long cal1(long long b) {
	if(b & 1) {
		long long cnt = qpow(C, (b + 1) / 2) * 2 + qpow(C, b * b);
		cnt += qpow(C, (b * b - 1) / 2 + 1);
		cnt %= MOD;
		cnt = cnt * inv(4) % MOD;
		return cnt;
	}else {
		long long cnt = qpow(C, b * b) + qpow(C, b / 2) * 2;
		cnt += qpow(C, (b * b) / 2);
		cnt %= MOD;
		cnt = cnt * inv(4) % MOD;
		return cnt;
	}
}
long long phi(long long x) {
	if(x == 1) return 1;
	long long ans = 1;
	for(int i = 0; i < dvh && dv[i].p * dv[i].p <= x; i++) {
		long long d = dv[i].p;
		if(x % d == 0) {
			x /= d;
			ans *= d - 1;
			while(x % d == 0) {
				x /= d;
				ans *= d;
			}
		}
	}
	if(x > 1) ans *= x - 1;
	return ans;
}
long long cal2(long long n, long long c) {
	long long ans = 0;
	for(long long i = 0; dd[i] * dd[i] <= n; i++) {
		long long d = dd[i];
		if(n % d == 0) {
			ans = (ans + phi(n / d) * qpow(c, d)) % MOD;
			if(d * d != n) {
				ans = (ans + phi(n / (n / d)) * qpow(c, n / d)) % MOD;
			}
		}
	}
	return ans * inv(n) % MOD;
}
long long ans = 0;
void dfs(int p = 0, long long b = 1) {
	if(p == dvh) {
		long long k = (A - 1) / (b * b);
		long long c = cal1(b);
		long long res = cal2(k, c);
		ans = (ans + res) % MOD;
		return ;
	}
	for(int i = 0; i * 2 <= dv[p].cnt; i++){
		dfs(p + 1, b);
		b *= dv[p].p;
	}
}
void dfs2(int p = 0, long long b = 1) {
	if(p == dvh) {
		dd[ddh++] = p;
		return ;
	}
	dfs2(p + 1, b);
	for(int i = 0; i < dv[p].cnt ; i++) {
		b *= dv[p].p;
		dfs2(p + 1, b);
	}
}
int main() {
	scanf("%d", &T);
	while(T--) {
		printf("Case %d: ", ++cas);
		scanf("%lld%lld", &A, &C);
		dvh = ddh = 0;
		A = A * A;
		getd(A - 1);
		dfs2();
		sort(dd,dd + ddh);;
		ans = 0;
		dfs();
		ans = ans * C % MOD;
		printf("%lld\n", ans);
	}
	return 0;
}
