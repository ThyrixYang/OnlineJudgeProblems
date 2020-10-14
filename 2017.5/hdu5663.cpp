#include <bits/stdc++.h>

const int MAXN = 10000020;
bool check[MAXN + 10];
int prime[MAXN + 10];
int mu[MAXN + 10];
long long F[MAXN + 10];
long long sum[MAXN + 10];
int is[MAXN + 10];
void Mobius(){
	memset(check, 0, sizeof check);
	mu[1] = 1;
	int tot = 0;
	is[1] = 1;
	for(long long  i = 2; i <= MAXN; i++){
		if(i * i <=MAXN) is[i * i] = 1;
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
	for(int i = 1; i <= MAXN; i++) {
		if(is[i]) {
			for(int j = 1; j * i <= MAXN; j++) {
				F[i * j] += mu[j];
			}
		}
	}
	for(int i = 1; i <= MAXN; i++)
		F[i] += F[i - 1];
}
int T, n, m;
std::vector<int> dv;
int main() {
	Mobius();
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		if(n > m) std::swap(n, m);
		long long ans = 0;
		for(int i = 1, j; i <= n; i = j + 1) {
			j = std::min(n / (n / i), m / (m / i));
			ans += (F[j] - F[i - 1]) * (n / i) * (m / i);
		}
		printf("%lld\n", (long long)n * (long long)m - ans);
	}
	return 0;
}
