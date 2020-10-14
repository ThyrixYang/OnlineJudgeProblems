#include <bits/stdc++.h>

long long qpow(long long a, long long p, long long mod) {
	long long ans = 1;
	a %= mod;
	while(p > 0) {
		if(p & 1) ans = ans * a % mod;
		a = a * a % mod;
		p >>= 1;
	}
	return ans;
}
typedef long long LL;
LL multi_mod(LL a, LL b, LL c) {
    a %= c;
    b %= c;
    LL ret = 0;
    while(b) {
        if(b&1) {
            ret += a;
            if(ret >= c) ret -= c;
        }
        a <<= 1;
        if(a>c) a-=c;
        b >>= 1;
    }
    return ret;
}
int T, n;
long long l, r;
long long p[20], a[20];
int v[20], vh = 0;
long long ans = 0;
int cas = 0;
void dfs(int pos, long long x, int f = 2) {
	if(pos == n) {
		if(f == 2) return;
		long long M = 7;
		for(int i = 0; i < vh; i++) M *= p[v[i]];
		long long res = 0;
		for(int i = 0; i < vh; i++) {
			long long x = multi_mod(a[v[i]], qpow(M / p[v[i]], p[v[i]] - 2, p[v[i]]), M);
			x = multi_mod(x, M / p[v[i]], M);
			res += x;
			res %= M;
		}
		ans += f * (x / M + (res <= x % M && res != 0));
		return;
	}
	dfs(pos + 1, x, f);
	v[vh++] = pos;
	if(f == 2) f = -1;
	dfs(pos + 1, x, -f);
	vh--;
}
int main() {
	freopen("./in", "r", stdin);
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		scanf("%lld%lld", &l, &r);
		for(int i = 0; i < n; i++)
			scanf("%lld%lld", &p[i], &a[i]);
		ans = 0;
		dfs(0, l  - 1);
		long long ans1 = ans;
		ans = 0;
		dfs(0, r);
		long long ans2 = ans;
		printf("Case #%d: %lld\n", ++cas,r / 7 - (l - 1) / 7 - (ans2 - ans1)); 
	}
	return 0;
}
