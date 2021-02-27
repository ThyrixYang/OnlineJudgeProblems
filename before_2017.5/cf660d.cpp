#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
struct Point{
	int x,y;
	Point(int x=0,int y=0):x(x),y(y){}
	void in(){scanf("%d%d",&x,&y);}
	Point operator + (const Point &C)const{
		return Point(x+C.x,y+C.y);
	}
	Point operator - (const Point &C)const{
		return Point (x-C.x,y-C.y);
	}
	bool operator < (const Point &C)const{
		if(x!=C.x) return x<C.x;
		return y<C.y;
	}
};
const int maxn=2005;
Point a[maxn];
int n;
map<Point,int> M;
int main(){
	freopen("/home/cwind/vimFile/in","r",stdin);
	cin>>n;
	for(int i=0;i<n;i++) a[i].in();
	int bh=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(i==j) continue;
			if(a[i].x<a[j].x) continue;
			if(a[i].x==a[j].x&&a[i].y<a[j].y) continue;
			++M[a[i]-a[j]];
		}
	}
	ll ans=0;
	map<Point,int>::iterator it=M.begin();
	while(it!=M.end()){
		ans+=it->second*(it->second-1)/2;
		it++;
	}
	cout<<ans/2<<endl;
	return 0;
}
