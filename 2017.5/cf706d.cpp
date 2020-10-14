#include <bits/stdc++.h>

const int MAXN = 1e7;
int ch[MAXN][2];
int cnt[MAXN];
int q;
int b[40];
char s[30];
void cal(int x) {
	for(int i = 0; i < 35; i++) {
		b[i] = (x & 1);
		x >>= 1;
	}
	std::reverse(b, b + 35);
}
int sz = 0;
void insert(int d) {
	int v = 0;
	for(int i = 0; i < 35; i++) {
		if(!ch[v][b[i]]) {
			ch[v][b[i]] = ++sz;
		}
		v = ch[v][b[i]];
		cnt[v] += d;
	}
}
int c = 0;
long long query() {
	if(c == 0) return 0;
	long long ans = 0;
	int v = 0;
	for(int i = 0; i < 35; i++) {
		if(cnt[ch[v][b[i] ^ 1]]) {
			v = ch[v][b[i] ^ 1];
			ans |= (1ll << (35 - i - 1));
		} else {
			v = ch[v][b[i]];
		}
	}
	return ans;
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> q;
	while(q--) {
		scanf("%s", s);
		long long x;
		scanf("%lld", &x);
		cal(x);
		if(s[0] == '+') {
			insert(1);
			c++;
		} else if(s[0] == '-') {
			insert(-1);
			c--;
		} else {
			long long ans = query();
			ans = std::max(ans, x);
			printf("%lld\n", ans);
		}
	}
	return 0;
}
