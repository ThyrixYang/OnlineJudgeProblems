#include <bits/stdc++.h>

const int MAXN = 200000 + 3000;
bool check[MAXN + 10];
int prime[MAXN + 10];
int mu[MAXN + 10];
std::vector<int> fac[MAXN];
void Mobius(){
	memset(check,false,sizeof(check));
	mu[1] = 1;
	int tot = 0;
	for(int i = 2; i <= MAXN; i++){
		if( !check[i] ){
			prime[tot++] = i;
			mu[i] = -1;
		}
		for(int j = 0; j < tot; j++){
			if(i * prime[j] > MAXN) break;
			check[i * prime[j]] = true;
			if( i % prime[j] == 0){
				mu[i * prime[j]] = 0;
				break;
			}
			else{
				mu[i * prime[j]] = -mu[i];
			}
		}
	}
}
int n, m;
struct BIT {
	long long a[MAXN];
	void add(int p, int x) {
		while(p < n + 33) a[p] += x, p += p & -p;
	}
	long long sum(int p) {
		long long ans = 0;
		while(p > 0) ans += a[p], p -= p & -p;
		return ans;
	}
	void clear(int n) {
		memset(a, 0, sizeof (long long) * (n + 3));
	}
}B;
int cas = 0;
int main() {
	freopen("./in", "r", stdin);
	Mobius();
	for(int i = 1; i < MAXN; i++) {
		for(int j = i; j < MAXN; j += i) {
			fac[j].push_back(i);
		}
	}
	while(scanf("%d%d", &n, &m) != EOF) {
		if(n == 0 && m == 0) break;
		printf("Case #%d:\n", ++cas);
		B.clear(n);
		while(m--) {
			int t;
			scanf("%d", &t);
			if(t == 1) {
				int x, v, d;
				scanf("%d%d%d", &x, &d, &v);
				if(x % d != 0) continue;
				x /= d;
				for(auto &y : fac[x]) {
					B.add(y * d, mu[y] * v);
				}
			} else {
				int x;
				scanf("%d", &x);
				long long ans = 0;
				for(int i = 1, j; i <= x; i++) {
					j = x / (x / i);
					ans += (B.sum(j) - B.sum(i - 1)) * (x / i);
					i = j;
				}
				printf("%lld\n", ans);
			}
		}
	}
	return 0;
}
