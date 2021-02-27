#include <bits/stdc++.h>

const int MAXN = 6e5;
const int mod = (119 << 23) + 1;  
const int G = 3;  //需求解mod的原根
const int NUM = 23;  //mod为2的几次幂

typedef long long ll;
using namespace std;
ll wn[NUM];  
ll qpow(ll a, ll b)  {  
	ll ans = 1;  
	a %= mod;  
	while(b)  {  
		if(b & 1) ans = ans * a % mod;  
		b >>= 1;  
		a = a * a % mod;  
	}  
	return ans;  
}  
  
void GetWn()  {  //预处理旋转因子
	for(int i=0; i<NUM; i++)  {  
		int t = 1 << i;  
		wn[i] = qpow(G, (mod - 1) / t);  
	}  
}  
void Rader(ll a[], int len)  { 
	int j = len >> 1;  
	for(int i=1; i<len-1; i++)  {  
		if(i < j) swap(a[i], a[j]);  
		int k = len >> 1;  
		while(j >= k)   {  
			j -= k;  
			k >>= 1;  
		}  
		if(j < k) j += k;  
	}  
}  
  
void NTT(ll a[], int len, int on)  {  
	Rader(a, len);  
	int id = 0;  
	for(int h = 2; h <= len; h <<= 1)  {  
		id++;  
		for(int j = 0; j < len; j += h)  {  
			ll w = 1;  
			for(int k = j; k < j + h / 2; k++)  {  
				ll u = a[k] % mod;  
				ll t = w * (a[k + h / 2] % mod) % mod;  
				a[k] = (u + t) % mod;  
				a[k + h / 2] = ((u - t) % mod + mod) % mod;  
				w = w * wn[id] % mod;  
			}  
		}  
	}  
	if(on == -1)  {  
		for(int i = 1; i < len / 2; i++)  
			swap(a[i], a[len - i]);  
		ll Inv = qpow(len, mod - 2);  
		for(int i = 0; i < len; i++)  
			a[i] = a[i] % mod * Inv % mod;  
	}  
}
int T;
int a[MAXN];
long long x1[MAXN],x2[MAXN];
long long fac[MAXN], inv[MAXN];
long long p2[MAXN];
int n;
int main() {
	freopen("./in", "r", stdin);
	GetWn();
	p2[0] = fac[0] = inv[0] = 1;
	for(int i = 1; i < 1e5 + 3000; i++) {
		fac[i] = fac[i - 1] * i % mod;
		inv[i] = qpow(fac[i], mod - 2);
		p2[i] = p2[i - 1] * 2 % mod;
	}
	std::cin >> T;
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		std::sort(a, a + n, std::greater<int>() );
		int len = 1;
		while(len <= n * 2) len <<= 1;
		for(int i = 0; i < n; i++) {
			x1[i] = (long long) a[i] * p2[n - i - 1] % mod * fac[i] % mod;
			x2[i] = inv[i];
		}
		std::reverse(x2, x2 + n);
		for(int i = n; i < len; i++) x1[i] = x2[i] = 0;
		NTT(x1, len, 1);
		NTT(x2, len, 1);
		for(int i = 0; i < len; i++) x1[i] = x1[i] * x2[i] % mod;
		NTT(x1, len, -1);
		long long ans  = 0;
		for(int i = n - 1; i < 2 * n - 1; i++) {
			printf("%lld ", ans = (ans + x1[i] * inv[i - n + 1] % mod) % mod);
		}
		puts("");
	}
	return 0;
}
