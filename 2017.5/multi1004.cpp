#include <bits/stdc++.h>

const double EPS = 1e-8;
const int MAXN = 2005;
const int MAXO = 1e5;

struct Point {
	double x, y;
	double minx, miny, maxx, maxy;
	int cnt;
	int ls, rs;
	Point(double x = 0, double y = 0): x(x), y(y) {}
	void in() {scanf("%lf%lf", &x, &y);}
	Point operator - (const Point &C) const {
		return Point(x - C.x, y - C.y);
	}
}ps[MAXN];
Point T[MAXO];
void up(int o) {
	int l = T[o].ls, r = T[o].rs;
	if(l) {
		T[o].minx = std::min(T[o].minx, T[l].minx);
		T[o].maxx = std::max(T[o].maxx, T[l].maxx);
	}
	if(r) {
		T[o].minx = std::min(T[o].minx, T[r].minx);
		T[o].maxx = std::max(T[o].maxx, T[r].maxx);
	}
}
int sz;
int wd;
bool cmp(const Point &a, const Point &b) {
	if(wd) return a.x < b.x;
	else return a.y < b.y;
}
#define mi ((l + r) >> 1)
void build(int &o, int l, int r, int w) {
	if(r - l <= 0) return ;
	o = ++sz;
	wd = w;
	nth_element(ps + l, ps + mi, ps + r, cmp);
	T[o] = ps[mi];
	T[o].cnt = r - l;
	T[o].ls = T[o].rs = 0;
	if(r - l <= 1) return;
	build(T[o].ls, l, mi, w ^ 1);
	build(T[o].rs, mi, r, w ^ 1);
	up(o);
}
double cal1(double a, double b, double c) {
	if((a - c) * (b - c) < 0) return 0;
	return std::min(std::fabs(a - c), std::fabs(b - c));
}
double cal2(double a, double b, double c) {
	return std::max(std::fabs(a - c), std::fabs(b - c));
}
#define sq(x) ((x) * (x))
int query(int o, Point p, double r) {
	if(!o) return 0;
	int ans = 0;
	double d = sqrt(sq(cal1(T[o].maxx, T[o].minx, p.x)) 
			+ sq(cal1(T[o].maxy, T[o].miny, p.y)));
	if(d > r) return 0;
	double d2 = sqrt(sq(cal2(T[o].maxx, T[o].minx, p.x)) 
			+ sq(cal2(T[o].maxx, T[o].miny, p.y)));
	if(d2 < r) return T[o].cnt;
	double d3 = sqrt(sq(T[o].x - p.x) + sq(T[o].y - p.y));
	if(d3 <= r + EPS) ans++;
	ans += query(T[o].ls, p, r);
	ans += query(T[o].rs, p, r);
	return ans;
}
int p[MAXN][MAXN];
double ang[MAXN][MAXN];
int n;
int main() {
	while(scanf("%d", &n) != EOF) {
		for(int i = 0; i < n; i++) ps[i].in();
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				p[i][j] = j;
				if(j == i) std::swap(p[i][0], p[i][j]);
			}
			for(int j = 1; j < n; j++) {
				Point res = p[j] - p[i];
				ang[j] = atan2(res.y, res.x);
			}
			std::sort(ang + 1, ang + n);
		}
		int root = 0;
		build(root, 0, n, 0);
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				Point a = ps[i], b = ps[j];
				Point c((a.x + b.x) / 2, (a.y + b.y) / 2);

			}
		}
	}
	return 0;
}
