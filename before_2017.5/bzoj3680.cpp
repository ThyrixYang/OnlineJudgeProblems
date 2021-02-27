#include <bits/stdc++.h>

using namespace std;

const double EPS=1e-8;
struct Point{
	double x,y;
	Point (double x=0,double y=0):x(x),y(y){}
	Point operator + (const Point &C)const{
		return Point (x+C.x,y+C.y);
	}
	Point operator - (const Point &C)const{
		return Point (x-C.x,y-C.y);
	}
	Point operator * (const double &c)const{
		return Point (x*c,y*c);
	}
	void in(){scanf("%lf%lf",&x,&y);}
	void out(){printf("%.3f %.3f",x,y);}
	Point norm(){
		double d=sqrt(x*x+y*y);
		if(fabs(d)<EPS) return *this;
		x/=d,y/=d;
		return *this;
	}
};
const int maxn=1e4+3000;
int n;
Point p[maxn];
double w[maxn];
Point ps[maxn];
Point ap;
double ans;
int main(){
	freopen("./in","r",stdin);
	cin>>n;
	for(int i=0;i<n;i++){
		p[i].in();
		scanf("%lf",&w[i]);
	}
	double alpha=0.8,L=1e4;
	for(int i=0;i<1000;i++){
		Point d;
		for(int j=0;j<n;j++){
			d=d+(p[j]-ap).norm()*w[j];
		}
		ap=ap+d.norm()*L;
		L*=alpha;
	}
	ap.out();
	return 0;
}
