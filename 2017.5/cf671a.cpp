#include <bits/stdc++.h>

using namespace std;

const int maxn=2e5;
struct Point{
	double x,y;
	Point (double x=0,double y=0):x(x),y(y){}
	void in(){scanf("%lf%lf",&x,&y);}
}p[maxn];
Point pa,pb,pc;
int n;
#define sq(x) ((x)*(x))
double dist(Point a,Point b){
	return sqrt(sq(a.x-b.x)+sq(a.y-b.y));
}
double dc[maxn],da[maxn],db[maxn];
int id1[maxn],id2[maxn];
bool cmpa(int a,int b){
	return da[a]-dc[a]<da[b]-dc[b];
}
bool cmpb(int a,int b){
	return db[a]-dc[a]<db[b]-dc[b];
}
int main(){
	freopen("./in","r",stdin);
	pa.in();pb.in();pc.in();
	cin>>n;
	for(int i=0;i<n;i++) p[i].in(),id2[i]=id1[i]=i,dc[i]=dist(pc,p[i]);
	for(int i=0;i<n;i++) da[i]=dist(pa,p[i]),db[i]=dist(pb,p[i]);
	double ans=0;
	for(int i=0;i<n;i++) ans+=dc[i]*2;
	sort(id1,id1+n,cmpa);
	sort(id2,id2+n,cmpb);
	double c=1e30;
	for(int i=0;i<min(n,4);i++){
		for(int j=0;j<min(n,4);j++){
			if(id1[i]==id2[j]) continue;
			if(da[id1[i]]+db[id2[j]]-dc[id1[i]]-dc[id2[j]]<c){
				c=da[id1[i]]+db[id2[j]]-dc[id1[i]]-dc[id2[j]];
			}
		}
	}
	c=min(c,da[id1[0]]-dc[id1[0]]);
	c=min(c,db[id2[0]]-dc[id2[0]]);
	printf("%.15f\n",ans+c);
	return 0;
}
