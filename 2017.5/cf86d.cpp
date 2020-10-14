#include <bits/stdc++.h>

const int maxn = 2e6;
struct Node {
	int l, r, id;
	void in(){scanf("%d%d", &l, &r);}
	bool operator < (const Node &C) const {
		return r < C.r;
	}
}q[maxn];
int n, t;
int a[maxn];
const int sz = 800;
std::vector<Node> buk[maxn / sz];
long long ans[maxn];
long long cnt[maxn];
long long res;
#define sq(x) ((x) * (x))
void lmovel(int &l) {
	l--;
	res -= sq(cnt[a[l]]) * a[l];
	cnt[a[l]]++;
	res += sq(cnt[a[l]]) * a[l];
}
void lmover(int &l) {
	res -= sq(cnt[a[l]]) * a[l];
	cnt[a[l]]--;
	res += sq(cnt[a[l]]) * a[l];
	l++;
}
void rmovel(int &r) {
	res -= sq(cnt[a[r]]) * a[r];
	cnt[a[r]]--;
	res += sq(cnt[a[r]]) * a[r];
	r--;
}
void rmover(int &r) {
	r++;
	res -= sq(cnt[a[r]]) * a[r];
	cnt[a[r]]++;
	res += sq(cnt[a[r]]) * a[r];
}
int main() {
	std::cin >> n >> t;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 0; i < t; i++) q[i].in(),q[i].id = i;
	for(int i = 0; i < t; i++)
		buk[q[i].l / sz].push_back(q[i]);
	for(int i = 0; i < maxn / sz; i++){
		std::sort(buk[i].begin(), buk[i].end());
		if(i & 1) std::reverse(buk[i].begin(), buk[i].end());
	}
	int ls =0,rs = 0;
	for(int i = 0; i < maxn / sz; i++) {
		for(int j = 0; j < buk[i].size(); j++) {
			int l = buk[i][j].l, r = buk[i][j].r;
			int id = buk[i][j].id;
			while(rs < r) rmover(rs);
			while(l < ls) lmovel(ls);
			while(rs > r) rmovel(rs);
			while(l > ls) lmover(ls);
			ans[id] = res;
		}
	}
	for(int i = 0; i < t; i++)
		printf("%lld\n", ans[i]);
	return 0;
}
