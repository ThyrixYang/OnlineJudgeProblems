#include <bits/stdc++.h>

using namespace std;

#define pb push_back
typedef long long ll;
const int maxn=3e5+3000;
const ll mod=1e9+7;
int n;
int a[maxn];
ll qpow(ll a,ll p){
	ll ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % mod;
		a = a * a % mod;
		p >>= 1;
	}
	return ans;
}
vector<int> factor[maxn];
int pri[maxn];
int np[maxn];
ll fac[maxn];
ll inv[maxn];
ll C[maxn];
ll sumc[maxn];
ll ssc[maxn];
ll p2[maxn];
void init(){
	for(int i = 2; i < maxn; i++){
		if(!np[i]) pri[++pri[0]] = i;
		for(int j = i; j < maxn; j += i){
			factor[j].pb(i);
			np[j] = 1;
		}
	}
	p2[0] = fac[0] = inv[0] = 1;
	for(int i = 1; i < maxn; i++ ) {
		p2[i] = p2[i-1] * 2 % mod;
		fac[i] = fac[i-1] * i % mod;
		inv[i] = qpow(fac[i], mod-2);
	}
	sumc[0] = C[0] = ssc[0] = 1;
	for(int i = 1; i <= n-1; i++){
		C[i] = fac[n-1] * inv[n-1-i] % mod * inv[i] % mod;
		sumc[i] = (sumc[i-1] + C[i]) % mod;
		ssc[i] = (ssc[i-1] + sumc[i]) % mod;
	}

}
ll geta(int k) {
	ll ans = p2[n-1] - ((n - k - 1 >= 0?2 * sumc[n - k - 1] : 0) % mod + C[n-k]) % mod;
	ans %= mod;
	if(ans<0) ans += mod;
	return ans;
}
ll pfix[maxn];
void pre(){
	for(int i = 1; i <= n; i++) {
		pfix[i] = pfix[i-1] + geta(i);
		pfix[i] %= mod;
	}
}
int cnt[maxn][70];
void cal(int a) {
	int x = a;
	for(int i = 0; i < factor[a].size(); i++) {
		int c = 0;
		while(x % factor[a][i] == 0) {
			c++;
			x /= factor[a][i];
		}
		cnt[factor[a][i]][c]++;
		cnt[factor[a][i]][0]--;
	}
}
void solve() {
	ll ans = 0;
	for(int i = 2; i < maxn; i++) {
		if(cnt[i][0] == n) continue;
		int cc = cnt[i][0];
		for(int j = 1; j < 64; j++){
			ans += j * (pfix[cc + cnt[i][j]] - pfix[cc]) % mod;
			ans %= mod;
			if(ans < 0) ans += mod;
			cc += cnt[i][j];
		}
	}
	cout << ans << endl;
}
int main(){
	freopen("./in","r",stdin);
	cin >> n;
	init();
	for(int i = 0; i < maxn; i++) cnt[i][0] = n;
	for(int i = 0; i < n; i++) {
		scanf("%d",&a[i]);
		cal(a[i]);
	}
	if(n == 1) {
		cout << 0 << endl;
		return 0;
	}
	pre();
	solve();
	return 0;
}
