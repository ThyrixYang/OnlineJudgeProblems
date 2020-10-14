#include <bits/stdc++.h>

const int MAXN = 100000;
bool check[MAXN + 10];
int prime[MAXN + 10];
int mu[MAXN + 10];
void mobius(){
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
long long w[MAXN];
void init() {
	for(int i = 1; i < MAXN; i++) {
		for(int j = 1; j * i < MAXN; j++) {
			int n = j * i;
			w[n] += mu[j] * i;
		}
	}
}
int f[MAXN];
long long ans;
int T, cas = 0;
int n, q;
struct Node {
	int l, r, id;
	Node(int l, int r, int id): l(l), r(r), id(id) {}
	bool operator < (const Node &C) const {
		return r < C.r;
	}
};
const int SZ = 205;
std::vector<Node> buk[SZ];
namespace my{
	std::vector<int>div[MAXN];
};
int cnt[MAXN];
long long C(long long x) {
	return x * (x - 1) / 2;
}
void del(int x) {
	for(int i = 0; i < my::div[x].size(); i++) {
		int d = my::div[x][i];
		ans -= C(f[d]) * w[d];
		f[d]--;
		ans += C(f[d]) * w[d];
	}
}
void add(int x) {
	for(int i = 0; i < my::div[x].size(); i++) {
		int d = my::div[x][i];
		ans -= C(f[d]) * w[d];
		f[d]++;
		ans += C(f[d]) * w[d];
	}
}
long long res[MAXN];
int a[MAXN];
int main() {
	mobius();
	init();
	std::cin >> T;
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++){
			my::div[i].clear();
			for(int d = 1; d * d <= a[i]; d++) {
				if(a[i] % d == 0) {
					my::div[i].push_back(d);
					if(d * d != a[i]) my::div[i].push_back(a[i] / d);
				}
			}
		}
		printf("Case #%d:\n", ++cas);
		memset(f, 0, sizeof f);
		ans = 0;
		for(int i = 0; i < SZ; i++) buk[i].clear();
		scanf("%d", &q);
		for(int i = 0; i < q; i++) {
			int l, r;
			scanf("%d%d", &l, &r);
			buk[l / SZ].push_back(Node(l, r, i));
		}
		for(int i = 0; i < 205; i++) {
			std::sort(buk[i].begin(), buk[i].end());
			if(i & 1) std::reverse(buk[i].begin(), buk[i].end());
		}
		int ls = 0, rs = 0;
		for(int i = 0; i < 205; i++) {
			for(int j = 0; j < buk[i].size(); j++) {
				int l = buk[i][j].l, r = buk[i][j].r;
				int id = buk[i][j].id;
				while(rs < r) add(++rs);
				while(ls > l) add(--ls);
				while(rs > r) del(rs--);
				while(ls < l) del(ls++);
				res[id] = ans;
			}
		}
		for(int i = 0; i < q; i++) printf("%lld\n", res[i]);
	}
	return 0;
}
