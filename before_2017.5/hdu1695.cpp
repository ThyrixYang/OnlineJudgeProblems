#include <bits/stdc++.h>

const int MAXN = 1000000;
bool check[MAXN+10];
int prime[MAXN+10];
int mu[MAXN+10];
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
int a, b, c, d, k;
int T, cas = 0;
long long F[MAXN];
int main() {
	Mobius();
	scanf("%d", &T);
	while(T--) {
		printf("Case %d: ", ++cas);
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		if(k == 0) {
			puts("0");
			continue;
		}
		if(b > d) std::swap(b, d);
		memset(F, 0, sizeof(long long) * (b + 20));
		for(int i = 1; i * k <= b; i++) {
			F[i * k] += mu[i];
		}
		for(int i = 1; i <= b; i++) F[i] += F[i - 1];
		long long ans = 0;
		for(int i = 1, j; i <= b; i = j + 1) {
			j = std::min(b / (b / i), d / (d / i));
			ans += (F[j] - F[i - 1]) * (b / i) * (d / i);
		}
		long long ans2 = 0;
		for(int i = 1, j; i <= b; i = j + 1) {
			j = b / (b / i);
			ans2 += (F[j] - F[i - 1]) * (b / i) * (b / i);
		}
		printf("%lld\n", ans - ans2 / 2);
	}

	return 0;
}
