#include <bits/stdc++.h>

const int MAXN = 2005;
const double EPS = 1e-10;
const double PI = acos(-1);
int sgn(double x) {
	if(std::fabs(x) < EPS) return 0;
	if(x < 0) return -1;
	return 1;
}
struct Point {
	long long x, y;
	double ang;
	Point(long long x = 0, long long y = 0): x(x), y(y) {}
	void in() {
		scanf("%lld%lld", &x, &y);
	}
	void out() {
		printf("%lld %lld %.2f\n", x, y, ang);
	}
	Point operator - (const Point &C) const {
		return Point(x - C.x, y - C.y);
	}
	long long operator ^ (const Point &C) const {
		return x * C.y - y * C.x;
	}
}a[MAXN], b[MAXN * 2];
double ang(Point a) {
	return atan2((double)a.y, (double)a.x);
}
int n;
bool cmp(const Point &p1, const Point &p2) {
	if(std::fabs(p1.ang - p2.ang) < EPS) return 0;
	return p1.ang < p2.ang;
}
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d", &n) != EOF) {
		for(int i = 0; i < n; i++) {
			a[i].in();
		}
		long long cnt0 = 0, cnt1 = 0, cnt2 = 0;
		for(int v = 0; v < n; v++) {
			for(int i = 0; i < n; i++) b[i] = a[i];
			std::swap(b[0], b[v]);
			for(int i = 1; i < n; i++) b[i].ang = ang(b[i] - b[0]);
			std::sort(b + 1, b + n, cmp);
			for(int i = 1; i < n; i++) b[i + n - 1].ang = b[i].ang + 2 * PI;
			//for(int i = 1; i < n; i++) b[i].out();
			for(long long s = 1, t1 = 1, t2 = 1, t3 = 1; s < n; s++) {
				while(t1 < n * 2 - 1 && sgn(b[t1].ang - b[s].ang - PI / 2) < 0) t1++;
				t2 = std::max(t2, t1);
				while(t2 < n * 2 - 1 && sgn(b[t2].ang - b[s].ang - PI) < 0) t2++;
				t3 = std::max(t2, t3);
				while(t3 < n * 2 - 1 && sgn(b[t3].ang - b[s].ang - PI) == 0) t3++;
				cnt0 += t1 - s - 1;
				cnt1 += t2 - t1;
				cnt2 += t3 - t2;
			}
		}
		//printf("%lld %lld %lld\n", cnt0, cnt1, cnt2);
		long long ans = 0;
		printf("%lld\n", (cnt0 - (cnt1 + cnt2 / 2) * 2) / 3);
	}
	return 0;
}
