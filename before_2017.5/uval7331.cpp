#include <bits/stdc++.h>

using namespace std;
#define se second
#define sq(x) ((x)*(x))
const double eps = 1e-8;
const double PI = acos(-1.0);
int sgn(double x){
	if(fabs(x) < eps)return 0;
	if(x < 0)return -1;
	else return 1;
}
struct Point{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
    int in(){ return (scanf("%lf%lf",&x,&y) != EOF);}
    void out(){printf("%.3f %.3f\n",x,y);}
    Point operator -(const Point &b)const{return Point(x - b.x,y - b.y);}
    Point operator +(const Point &b)const{return Point(x + b.x,y + b.y);}
    double operator ^(const Point &b)const{return x*b.y - y*b.x;}
    double operator *(const Point &b)const{return x*b.x + y*b.y;}
	Point operator /(const double p)const{return (*this)*(1.0/p);}
    Point operator *(const double p)const{return Point(x*p,y*p);}
    bool operator ==(const Point b)const{return sgn(x-b.x)==0&&sgn(y-b.y)==0;}
};
double dist(Point A,Point B){
	return sqrt(sq(A-B));
}
struct Line{
	Point s,e;
	Line(){}
	Line(Point _s,Point _e){
		s = _s;e = _e;
	}
	double len(){return dist(s,e);}
	pair<int,Point> operator &(const Line &b)const{
		Point res = s;
		if(sgn((s-e)^(b.s-b.e)) == 0){
			if(sgn((s-b.e)^(b.s-b.e)) == 0)
				return make_pair(0,res);
			else return make_pair(1,res);
		}
		double t = ((s-b.s)^(b.s-b.e))/((s-e)^(b.s-b.e));
		res.x += (e.x-s.x)*t;
		res.y += (e.y-s.y)*t;
		return make_pair(2,res);
	}
};
bool Seg_inter_line(Line l1,Line l2){
	return sgn((l2.s-l1.e)^(l1.s-l1.e))*sgn((l2.e-l1.e)^(l1.s-l1.e)) <= 0;
}
Point p[5];
Point tmp[20];
Point c[4];
Line s[4];
int h;
bool _cmp(Point p1,Point p2){
	double t = (p1-tmp[0])^(p2-tmp[0]);
	if(sgn(t) > 0)return true;
	else if(sgn(t) == 0 && sgn(dist(p1,tmp[0]) - dist(p2,tmp[0])) <= 0)
		return true;
	else return false;
}
double area() {
	for(int i = 0; i < h; i++) {
		if(tmp[i].y < tmp[0].y) std::swap(tmp[i], tmp[0]);
		else if(tmp[i].x < tmp[0].y) std::swap(tmp[i], tmp[0]);
	}
	std::sort(tmp + 1, tmp + h, _cmp);
	double res = 0;
	for(int i = 0;i < h;i++)
		res += (tmp[i]^tmp[(i+1)%h])/2;
	return fabs(res);
}
double doup() {
	h = 0;
	Line cut(c[0], c[1]);
	for(int i = 0; i < 4; i++) {
		if(Seg_inter_line(cut, s[i])) {
			tmp[h++] = (cut & s[i]).second;
		}
	}
	for(int i = 0; i < 4; i++) {
		if(p[i].y >= 0.5) tmp[h++] = p[i];
	}
	return area();
}
double dodown() {
	h = 0;
	Line cut(c[2], c[3]);
	for(int i = 0; i < 4; i++) {
		if(Seg_inter_line(cut, s[i])) {
			tmp[h++] = (cut & s[i]).second;
		}
	}
	for(int i = 0; i < 4; i++) {
		if(p[i].y <= -0.5) tmp[h++] = p[i];
	}
	return area();
}
double doleft() {
	h = 0;
	Line cut(c[0], c[2]);
	for(int i = 0; i < 4; i++) {
		if(Seg_inter_line(cut, s[i])) {
			tmp[h++] = (cut & s[i]).second;
		}
	}
	for(int i = 0; i < 4; i++) {
		if(p[i].x <= -0.5) tmp[h++] = p[i];
	}
	return area();
}
double doright() {
	h = 0;
	Line cut(c[1], c[3]);
	for(int i = 0; i < 4; i++) {
		if(Seg_inter_line(cut, s[i])) {
			tmp[h++] = (cut & s[i]).second;
		}
	}
	for(int i = 0; i < 4; i++) {
		if(p[i].x >= 0.5) tmp[h++] = p[i];
	}
	return area();
}
int main() {
	freopen("./in", "r", stdin);
	c[0] = Point(-0.5, 0.5);
	c[1] = Point(0.5, 0.5);
	c[2] = Point(-0.5, -0.5);
	c[3] = Point(0.5, -0.5);
	while(p[0].in()) {
		for(int i = 1; i < 4; i++) p[i].in();
		s[0] = Line(p[0], p[1]);
		s[1] = Line(p[1], p[2]);
		s[2] = Line(p[2], p[3]);
		s[3] = Line(p[3], p[0]);
		double ans = 0;
		ans += 6 * doup() * 5;
		ans += 1 * dodown() * 5;
		ans += 3 * doright() * 5;
		ans += 4 * doleft() * 5;
		ans += 5 * (5 * 5) * 4;
		ans /= (5 * 5 * 5.0 - 1);
		printf("%.15f\n", ans);
	}
	return 0;
}
