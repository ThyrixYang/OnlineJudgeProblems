#include <bits/stdc++.h>

const int MAXN = 1e4 + 3;
typedef unsigned long long ull;
const ull H = 19;
ull hasha[MAXN];
ull hashb[MAXN];
ull ph[MAXN];
int n;
char a[MAXN], b[MAXN];
inline ull getHash(int l, int r, ull *h) {
	return h[l] - h[r] * ph[r - l];
}
std::bitset<MAXN> bs1[MAXN], bs2[MAXN];
std::bitset<MAXN> ans, tmp;
int main() {
	freopen("./1002.in", "r", stdin);
	ph[0] = 1;
	for(int i = 1; i < MAXN; i++) ph[i] = ph[i - 1] * H;
	while(scanf("%s%s", a, b) != EOF) {
		ans.reset();
		n = strlen(a);
		hasha[n] = hashb[n] = 0;
		for(int i = n - 1; i >= 0; i--) {
			hasha[i] = (hasha[i + 1] * H + a[i]);
			hashb[i] = (hashb[i + 1] * H + b[i]);
		}
		for(int i = 0; i <= n; i++) {
			bs1[i].reset();
			bs2[i].reset();
		}
		puts("set");
		for(int i = 0; i < n; i++) {
			for(int k = 0; k + i <= n; k++) {
				if(getHash(0, i, hasha) == getHash(k, k + i, hashb)){}
			}
		}
		for(int i = 0; i < n; i++) {
			for(int k = 0; k + i <= n; k++) {
				if(getHash(i, i + k, hasha) == getHash(0, k, hashb)){}
			}
		}
		puts("dd");
		for(int i = 0; i < n; i++) {
			tmp = bs1[i] & bs2[i];
			tmp <<= i;
			ans |= tmp;
		}
		for(int i = 1; i <= n; i++) {
			if(ans[i]) printf("1");
			else printf("0");
		}
		puts("");
	}
	return 0;
}
