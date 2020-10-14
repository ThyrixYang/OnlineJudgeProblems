#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int MAXN = 1005;
const long long MOD = 1e9 + 7;
long long qpow(long long a, long long p) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
struct Line {
	long long a, b, c;
	Line(long long  x1, long long y1, long long x2, long long y2) {
		a = x1 - x2;
		b = y1 - y2;
		c = x1 * y2 - x2 * y1;
		long long g = std::__gcd(a, b);
		g = std::__gcd(g, c);
		if(a == b && b == c && a == 0) return ;
		if(g * a < 0) g = -g;
		if(a == 0 && g * b < 0) g = -g;
		if(a == 0 && b == 0 && g * c < 0) g = -g;
		a /= g, b /= g, c /= g;
	}
	bool operator < (const Line &C) const {
		if(a != C.a) return a < C.a;
		if(b != C.b) return b < C.b;
		return c < C.c;
	}
};
long long Hash(const pair<int, int> &a) {
	return (long long)a.first * MOD + a.second;
}
long long Hash(const Line &L) {
	return (long long)L.a * 123433557 + (long long)L.b * MOD + (long long)L.c;
}
int T, n;
int X[MAXN], Y[MAXN];
pair<int, int> ps[MAXN];
int cc[MAXN];
int main() {
	std::cin >> T;
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			scanf("%d%d", &X[i], &Y[i]);
			ps[i] = make_pair(X[i], Y[i]);
		}
		unordered_map<long long, int> cnt;
		for(int i = 0; i < n; i++) 
			++cnt[Hash(make_pair(X[i], Y[i]))];
		std::sort(ps, ps + n);
		n = unique(ps, ps + n) - ps;
		unordered_map<long long, vector<int> > M;
		for(int i = 0; i < n; i++) cc[i] = cnt[Hash(ps[i])];
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				Line tmp = Line(ps[i].first, ps[i].second, ps[j].first, ps[j].second);
				M[Hash(tmp)].push_back(i);
				M[Hash(tmp)].push_back(j);
			}
		}
		unordered_map<long long, vector<int> >::iterator it = M.begin();
		long long ans = 0;
		for(int i = 0; i < n; i++) {
			if(cc[i] > 1){
				ans += qpow(2, cc[i]) - 1 - cc[i];
				ans %= MOD;
			}
		}
		for(;it != M.end(); it++) {
			vector<int> &v = it->second;
			sort(v.begin(), v.end());
			v.erase(unique(v.begin(), v.end()), v.end());
			long long c = 0;
			for(int j = 0; j < v.size(); j++) {
				c += cc[v[j]];
				if(cc[v[j]] > 1) {
					ans = (ans - qpow(2, cc[v[j]]) + 1 + MOD) % MOD;
				}
			}
			if(c <= 1) continue;
			ans += qpow(2, c) - c - 1;
			ans %= MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
