#include <bits/stdc++.h>

const double EPS = 1e-7;
struct Point {
	double x, y;
	Point(double x = 0, double y = 0): x(x) , y(y) {}
	double operator ^ (const Point &C) const {
		return x * C.y - C.x * y;
	}
	Point operator + (const Point &C) const {
		return Point(x + C.x, y + C.y);
	}
	Point operator - (const Point &C) const {
		return Point(x - C.x, y - C.y);
	}
	double operator * (const Point &C) const {
		return x * C.x + y * C.y;
	}
	void in() {
		scanf("%lf%lf", &x, &y);
	}
	void out() {
		printf("%.2f %.2f\n", x, y);
	}
};
Point ret[3];
struct Line {
	Point s, e;
	Line() {}
	Line(Point s, Point e): s(s), e(e) {}
};
Point PointToLine(Point P, Line L) {
	Point result;
	double t = ((P - L.s) * (L.e - L.s)) / ((L.e - L.s) * (L.e - L.s));
	result.x = L.s.x + (L.e.x - L.s.x) * t;
	result.y = L.s.y + (L.e.y - L.s.y) * t;
	return result;
}
int sgn(double x) {
	if(std::fabs(x) < EPS) return 0;
	if(x > 0) return 1;
	return -1;
}
int T;
#define sq(x) ((x) * (x))
void circle_cross_line(Point a, Point b, Point o, double r) {
	double x0 = o.x, y0 = o.y;
	double x1 = a.x, y1 = a.y;
	double x2 = b.x, y2 = b.y;
	double dx = x2 - x1, dy = y2 - y1;
	double A = dx * dx + dy * dy;
	double B = 2 * dx * (x1 - x0) + 2 * dy * (y1 - y0);
	double C = sq(x1 - x0) + sq(y1 - y0) - sq(r);
	double delta = B * B - 4 * A * C;
	if(sgn(delta) >= 0) {
		double t1 = (-B - sqrt(delta)) / (2 * A);
		double t2 = (-B + sqrt(delta)) / (2 * A);
		ret[0] = Point(x1 + t1 * dx, y1 + t1 * dy);
		ret[1] = Point(x1 + t2 * dx, y1 + t2 * dy);
	}
}
double dist(Point a, Point b) {
	return sqrt(sq(a - b));
}
Point A, B, O, V;
double r;
int cas = 0;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		printf("Case #%d: ", ++cas);
		O.in();
		scanf("%lf", &r);
		A.in();
		V.in();
		B.in();
		Line la(A, A + V);
		Point da = PointToLine(O, la);
		if(sgn(dist(da, O) - r) >= 0 || sgn((O - A) * V) <= 0) {
			if(sgn((B - A) * V) > 0 && sgn((B - A) ^ V) == 0) puts("Yes");
			else puts("No");
		} else {
			circle_cross_line(la.s, la.e, O, r);
			Point c = ret[0];
			if(dist(c, A) > dist(ret[1], A)) c = ret[1];
			if(sgn(dist(c, A) - dist(A, B)) >= 0) {
				if(sgn((B - A) * V) > 0 && sgn((B - A) ^ V) == 0) {
					puts("Yes");
					continue;
				}
			}
			Line lc = Line(c, O);
			Point ref = PointToLine(A, lc);
			ref = ref - A + ref;
			if(sgn((B - c) * (ref - c)) > 0 && sgn((B - c) ^ (ref - c)) == 0)
				puts("Yes");
			else puts("No");
		}
	}
	/*circle_cross_line(Point(0, 2), Point(0, -3), Point(0, 0), 1);
	ret[0].out();
	ret[1].out();*/
	return 0;
}
