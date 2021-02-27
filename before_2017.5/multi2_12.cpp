#include <bits/stdc++.h>

const int MAXN = 1e5+300;
int T, n, m;
char s[MAXN], p[MAXN];
const long long H = 131;
const long long MOD = 1e9 + 9;

long long fac[MAXN];
long long hashs[MAXN], hashp[MAXN];
long long gets(int l, int r) {
	return (hashs[l] - hashs[r] * fac[r - l] % MOD + (MOD << 1)) % MOD;
}
long long getp(int l, int r) {
	return (hashp[l] - hashp[r] * fac[r - l] % MOD + (MOD << 1)) % MOD;
}
std::set<long long> S;
int test(int a) {
	if(a + m > n) return 0;
	for(int pos = a; pos <= a + m; pos++) {
		if(pos == a + m) return 1;
		if(s[pos] != p[pos - a]) {
			if(pos == a + m - 1) return 0;
			if(s[pos] == p[pos - a + 1] && s[pos + 1] == p[pos - a]) {
				pos++;
				continue;
			}else return 0;
		}
		int l = pos + 1, r = a + m + 1;
		while(r - l > 1) {
			int mid = (r + l) >> 1;
			if(gets(pos, mid) == getp(pos - a, mid - a)) l = mid;
			else r = mid;
		}
		if(l == a + m) return 1;
		pos = l - 1;
	}
}
int main() {
	freopen("./in", "r", stdin);
	fac[0] = 1;
	for(int i = 1; i < MAXN; i++) fac[i] = fac[i - 1] * H % MOD;
	std::cin >> T;
	while(T--) {
		S.clear();
		scanf("%d%d", &n, &m);
		scanf("%s", s);
		scanf("%s", p);
		hashs[n] = 0;
		hashp[m] = 0;
		for(int i = n - 1; i >= 0; i--) hashs[i] = (hashs[i + 1] * H + s[i]) % MOD;
		for(int i = m - 1; i >= 0; i--) hashp[i] = (hashp[i + 1] * H + p[i]) % MOD;
		for(int i = 0; i < n; i++) {
			long long h = gets(i, i + m);
			if(S.find(h) != S.end()) {
				printf("1");
				continue;
			}
			if(test(i)) printf("1"),S.insert(h);
			else printf("0");
		}
		puts("");
	}
	return 0;
}
