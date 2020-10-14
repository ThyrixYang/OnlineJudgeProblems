#include <bits/stdc++.h>

const int maxn = 1e5;
int n, K;
struct Point {
	int x[5];
	void in() {
		for(int i = 0; i < K; i++) scanf("%d", &x[i]);
	}
	void set1() {
		for(int i = 0; i < K; i++) x[i] = 1e9;
	}
	void set0() {
		for(int i = 0; i < K; i++) x[i] = -1e9;
	}
	void out() {
		for(int i = 0; i < K; i++) {
			printf("%d", x[i]);
			if(i < K - 1) printf(" ");
		}
		puts("");
	}
};
#define sq(x) ((x) * (x))
int dist2(const Point &p1, const Point &p2) {
	int ans = 0;
	for(int i = 0; i < K; i++) {
		ans += sq(p1.x[i] - p2.x[i]);
	}
	return ans;
}
int cmpKey;
bool cmp(const Point &a,const Point &b) {
	return a.x[cmpKey] < b.x[cmpKey];
}
int ls[maxn], rs[maxn];
Point p[maxn], read[maxn];
Point Max[maxn],Min[maxn];
int sz;
int root;
Point tar;
Point close[20];
int h, m;
int md(int mn, int mx, int x) {
	if((mn - x) * (mx - x) <= 0) return 0;
	return std::min(sq(mn - x), sq(mx - x));
}
void update(Point a) {
	if(h < m) close[h++] = a;
	if(dist2(close[h - 1], tar) > dist2(a, tar)) close[h - 1] = a;
	for(int i = h - 1; i > 0; i--) {
		if(dist2(tar, close[i]) < dist2(tar, close[i - 1])) {
			std::swap(close[i], close[i - 1]);
		}
	}
}
void build(int l, int r, int &o, int d) {
	if(l >= r) return;
	o = ++sz;
	cmpKey = d;
	std::sort(read + l, read + r, cmp);
	int mid = (l + r) >> 1;
	p[o] = read[mid];
	ls[o] = rs[o] = 0;
	Max[o].set0(), Min[o].set1();
	for(int i = l; i < r; i++) {
		for(int j = 0; j < K; j++) {
			Max[o].x[j] = std::max(Max[o].x[j], read[i].x[j]);
			Min[o].x[j] = std::min(Min[o].x[j], read[i].x[j]);
		}
	}
	build(l, mid, ls[o], (d + 1) % K);
	build(mid + 1, r, rs[o], (d + 1) % K);
}
void query(int o) {
	if(o == 0) return;
	int mind = 0;
	for(int i = 0; i < K; i++) {
		mind += md(Min[o].x[i], Max[o].x[i], tar.x[i]);
	}
	if(h == m && mind >= dist2(close[h - 1], tar)) return;
	update(p[o]);
	query(ls[o]);
	query(rs[o]);
}
int main() {
	while(std::cin >> n >> K){
		for(int i = 0; i < n; i++)
			read[i].in();
		sz = 0;
		build(0, n, root, 0);
		int t;
		scanf("%d", &t);
		while(t--) {
			tar.in();
			scanf("%d", &m);
			h = 0;
			query(root);
			printf("the closest %d points are:\n",m);
			for(int i = 0; i < h; i++) {
				close[i].out();
			}
		}
	}
	return 0;
}
