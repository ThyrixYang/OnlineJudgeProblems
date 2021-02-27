#include <iostream>
#include <cstdio>
#include <algorithm>
const int MAXN = 2e5 + 10;
const int MAXO = MAXN * 33;

struct Node {
    int cnt, ls, rs;
    long long val;
}T[MAXO];
int n, m, X, p;
std::pair<int, int> ps[MAXN];
int dic[MAXN], dh;
int sz;
int root[MAXN];
inline int sgn(int x) {
    if(x > 0) return 1;
    if(x < 0) return -1;
    return 0;
}
#define mi ((l + r) >> 1)
void insert(int &o, int l, int r, int p, int d) {
    T[++sz] = T[o];
    o = sz;
    T[o].val += d;
    T[o].cnt += sgn(d);
    if(r - l <= 1) return;
    if(p < mi) insert(T[o].ls, l, mi, p, d);
    else insert(T[o].rs, mi, r, p, d);
}
#define P std::pair<long long, int>
#define mp std::make_pair
P query(int o, int l, int r, int k) {
	if(k == 0) return mp(0ll, 0);
	if(r - l <= 1) {
		if(T[o].cnt <= k) return mp(T[o].val, T[o].cnt);
		else return mp(dic[l] * k, k);
	}
    long long ans = 0;
    int c = 0;
    if(T[o].cnt <= k) return mp(T[o].val, T[o].cnt);
    P res = query(T[o].ls, l, mi, k);
    ans = res.first;
    c = res.second;
	res = P(0, 0);
    if(k - c > 0)  res = query(T[o].rs, mi, r, k - c);
    return mp(ans + res.first, c + res.second);
}
#define idx(x) (std::lower_bound(dic, dic + dh, std::abs(x)) - dic)
int main() {
	freopen("./in", "r", stdin);
	freopen("./out", "w", stdout);
	while(scanf("%d%d%d%d", &n, &m, &X, &p) != EOF) {
		dh = 0;
		for(int i = 0; i < n; i++) {
            int l, r, d;
            scanf("%d%d%d", &l, &r, &d);
            ps[i * 2] = std::make_pair(l, d);
            ps[i * 2 + 1] = std::make_pair(r + 1, -d);
            dic[dh++] = d;
        }
        std::sort(dic, dic + dh);
        std::sort(ps, ps + n * 2);
        dh = std::unique(dic, dic + dh) - dic;
        int sz = 0;
        root[0] = 0;
        for(int x = 1, i = 0; x <= X; x++) {
            root[x] = root[x - 1];
            while(i < n * 2 && ps[i].first == x) {
				insert(root[x], 0, dh, idx(ps[i].second), ps[i].second);
				i++;
			}
        }
		long long pre = 1;
		while(m--) {
			int x, a, b, c;
			scanf("%d%d%d%d", &x, &a, &b, &c);
			long long K = (a * pre + b) % c;
			P res = query(root[x], 0, dh, K);
			if(pre > p) res.first *= 2;
			printf("%lld\n", res.first);
			pre = res.first;
		}
	}
	return 0;
}
