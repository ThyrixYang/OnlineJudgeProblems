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
struct Line{
	Point s,e;
	Line(){}
	Line(Point _s,Point _e){
		s = _s;e = _e;
	}
	double len(){return dist(s,e);}
	Point getVer(){//单位长度垂线，在该直线的逆时针方向
		Point res(s.y-e.y,e.x-s.x);
		res=res.normP();
		return res;
	}
	//两直线相交求交点
	//第一个值为0表示直线重合,为1表示平行,为0表示相交,为2是相交
	//只有第一个值为2时,交点才有意义
	pair<int,Point> operator &(const Line &b)const{
		Point res = s;
		if(sgn((s-e)^(b.s-b.e)) == 0){
			if(sgn((s-b.e)^(b.s-b.e)) == 0)
				return make_pair(0,res);//重合
			else return make_pair(1,res);//平行
		}
		double t = ((s-b.s)^(b.s-b.e))/((s-e)^(b.s-b.e));
		res.x += (e.x-s.x)*t;
		res.y += (e.y-s.y)*t;
		return make_pair(2,res);
	}
};
struct circle{
	Point cen;
	double r;
	Point getPoint(double ang){
		return cen+Point(r*cos(ang),r*sin(ang));
	}
};
Point NearestPointToLineSeg(Point P,Line L){
	Point result;
	double t = ((P-L.s)*(L.e-L.s))/((L.e-L.s)*(L.e-L.s));
	if(t >= 0 && t <= 1){
		result.x = L.s.x + (L.e.x - L.s.x)*t;
		result.y = L.s.y + (L.e.y - L.s.y)*t;
	}
	else{
		if(dist(P,L.s) < dist(P,L.e))
			result = L.s;
		else result = L.e;
	}
	return result;
}
double ang(Point a,Point b){
	return acos((a*b)/(a.normV()*b.normV()));
}
Point getOutPoint(Point a,Point b,Point c){
	Point ver=Line(a,b).getVer();
	Point mid=(a+b)/2;
	if(sgn((mid-c)*(ver))<0) ver=ver*(-1);
	double len=dist(a,b);
	return mid+ver*sqrt(3)/2*len;
}
Point fermat(Point a,Point b,Point c){
	double angx=PI*2/3;
	if(sgn(ang(b-a,c-a)-angx)>=0) return a;
	if(sgn(ang(a-b,c-b)-angx)>=0) return b;
	if(sgn(ang(a-c,b-c)-angx)>=0) return c;
	Point a1=getOutPoint(b,c,a);
	Point b1=getOutPoint(a,c,b);
	return (Line(a1,a)&Line(b1,b)).se;
}
double getDist(Point a,Point b,Point c){
	Point res=fermat(a,b,c);
	return dist(a,res)+dist(b,res)+dist(c,res);
}
Point A,B;
circle C;
#define rep(x) for(int kkk=0;kkk<x;kkk++)
int main(){
	freopen("/home/cwind/vimFile/in","r",stdin);
	A.in();B.in();C.cen.in();
	scanf("%lf",&C.r);
	Point near=NearestPointToLineSeg(C.cen,Line(A,B));
	double dac=dist(A,C.cen),dbc=dist(B,C.cen);
	if(sgn(dist(near,C.cen)-C.r)<0){
		double ang1=ang(A-C.cen,B-C.cen);
		double anga=acos(C.r/dac);
		double angb=acos(C.r/dbc);
		double arc=C.r*(ang1-anga-angb);
		double lena=sqrt(sq(dac)-sq(C.r));
		double lenb=sqrt(sq(dbc)-sq(C.r));
		printf("%.15f\n",lena+lenb+arc);
	}else{
		double l=0,r=PI*2;
		Point p1,p2;
		rep(100){
			double midl=(r-l)/3+l;
			double midr=(r-l)*2/3+l;
			p1=C.getPoint(midl),p2=C.getPoint(midr);
			double ansl=getDist(p1,A,B),ansr=getDist(p2,A,B);
			if(ansl<ansr) r=midr;
			else l=midl;
		}
		printf("%.15f\n",getDist(p1,A,B));
	}
	return 0;
}
