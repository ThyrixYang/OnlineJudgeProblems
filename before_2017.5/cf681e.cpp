#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Point{
	ll x,y;
	Point(ll x=0,ll y=0):x(x),y(y){}
	void in(){scanf("%lld%lld",&x,&y);}
	Point operator - (const Point &C)const{
		return Point (x-C.x,y-C.y);
	}
};
#define sq(x) ((x)*(x))
ll dist2(Point a,Point b){
	return sq(a.x-b.x)+sq(a.y-b.y);
}
const ll maxn=2e5;
long double len,T;
ll n;
Point ps[maxn],p0;
ll r[maxn];
#define mp make_pair
vector<pair<long double,int> > seg;
const double eps=1e-8;
const long double pi=acos(-1);
int main(){
	freopen("./in","r",stdin);
	p0.in();
	cin>>len>>T;
	len*=T;
	cin>>n;
	for(int i=0;i<n;i++) ps[i].in(),scanf("%lld",&r[i]);
	for(int i=0;i<n;i++) ps[i]=ps[i]-p0;
	for(int i=0;i<n;i++){
		if(dist2(ps[i],Point(0,0))<=sq(r[i])){
			puts("1");
			return 0;
		}
		long double dir=atan2(ps[i].y,ps[i].x)+pi;
		long double d=sqrt((double)dist2(ps[i],Point(0,0)));
		if(len+r[i]<d+eps) continue;
		long double len1=sqrt(sq(d)-sq(r[i]));
		long double theta;
		if(len1<len+eps){
			theta=asin(r[i]/d);
		}else{
			theta=acos((sq(len)+sq(d)-sq((long double)r[i]))/(2*d*len));
		}
		long double ang1=dir-theta,ang2=dir+theta;
		if(ang2>2*pi) ang1-=2*pi,ang2-=2*pi;
		if(ang1<0){
			seg.push_back(mp(2*pi+ang1,1));
			seg.push_back(mp(2*pi,-1));
			seg.push_back(mp(0,1));
			seg.push_back(mp(ang2,-1));
		}else{
			seg.push_back(mp(ang1,1));
			seg.push_back(mp(ang2,-1));
		}
	}
	sort(seg.begin(),seg.end());
	long double ans=0;
	int c=0;
	long double last=0;
	for(int i=0;i<seg.size();i++){
		long double x=seg[i].first;
		if(c>0) ans+=x-last;
		last=x;
		c+=seg[i].second;
	}
	printf("%.15f\n",(double)(ans/(2*pi)));
	return 0;
}
