#include <bits/stdc++.h>

using namespace std;
const int len = 1 << 18;
typedef long long ll;
const int MAXN = 1 << 19;
const int mod = (119 << 23) + 1;  
const int G = 3;  //需求解mod的原根
const int NUM = 23;  //mod为2的几次幂


ll  wn[NUM];  
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
char s1[MAXN], s2[MAXN];
long long x1[5][MAXN], x2[5][MAXN], x3[MAXN];
const int maxn = 5e4 + 300;
int cnt[5][5][maxn];
int n;
int p[20];
int sum[MAXN];
int main() {
	freopen("./in", "r", stdin);
	GetWn();
	scanf("%s", s1);
	scanf("%s", s2);
	n = strlen(s1);
	for(int i = 0; i < n; i++) s1[i] -= 'A';
	for(int i = 0; i < n; i++) s2[i] -= 'a';
	std::reverse(s2, s2 + n);
	for(int i = 0; i < 5; i++) {
		for(int k = 0; k < n; k++) 
			if(s1[k] == i) x1[i][k] = x1[i][k + n] = 1;
		NTT(x1[i], len, 1);
	}
	for(int i = 0; i < 5; i++) {
		for(int k = 0; k < n; k++)
			if(s2[k] == i) x2[i][k] = 1;
		NTT(x2[i], len, 1);
	}
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			for(int k = 0; k < len; k++) x3[k] = x1[i][k] * x2[j][k];
			NTT(x3, len, -1);
			for(int k = n - 1; k <= n * 2; k++) cnt[i][j][k - n + 1] = x3[k];
		}
	}
	for(int i = 0; i < 5; i++) p[i] = i;
	int ans = 0;
	do {
		std::memset(sum, 0, sizeof (int) * (n + 3));
		for(int i = 0; i < 5; i++) {
			for(int j = 0; j <= n + 1; j++) {
				sum[j] += cnt[i][p[i]][j];
			}
		}
		for(int i = 0; i <= n + 1; i++) ans = std::max(ans, sum[i]);
	}while(std::next_permutation(p, p + 5));
	std::cout << n - ans << std::endl;
	return 0;
}
