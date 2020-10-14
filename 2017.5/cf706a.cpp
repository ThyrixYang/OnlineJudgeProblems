#include <bits/stdc++.h>

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
    void in(){scanf("%lf%lf",&x,&y);}
    void out(){printf("%.3f %.3f\n",x,y);}
    Point operator -(const Point &b)const{return Point(x - b.x,y - b.y);}
    Point operator +(const Point &b)const{return Point(x + b.x,y + b.y);}
    double operator ^(const Point &b)const{return x*b.y - y*b.x;}
    double operator *(const Point &b)const{return x*b.x + y*b.y;}
	Point operator /(const double p)const{return (*this)*(1.0/p);}
    Point operator *(const double p)const{return Point(x*p,y*p);}
    bool operator ==(const Point b)const{return sgn(x-b.x)==0&&sgn(y-b.y)==0;}
    //绕原点旋转角度B(弧度值),后x,y的变化
    Point transXY(double B){
        double tx = x,ty = y;
        x = tx*cos(B) - ty*sin(B);
        y = tx*sin(B) + ty*cos(B);
        return *this;
    }
    double normV(){return sqrt(x*x+y*y);}
    Point normP(){double v=normV();return Point(x/v,y/v);}
};
double dist(Point A,Point B){
	return sqrt(sq(A-B));
}
Point c;
int n;
int main() {
	freopen("./in", "r", stdin);
	double ans = 1e18;
	c.in();
	std::cin >> n;
	for(int i = 0; i < n; i++) {
		Point x;
		double v;
		x.in();
		scanf("%lf", &v);
		ans = std::min(ans, dist(c, x) / v);
	}
	printf("%.15f\n", ans);
	return 0;
}
