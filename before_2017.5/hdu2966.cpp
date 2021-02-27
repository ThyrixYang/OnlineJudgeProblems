#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxo=2e5;
int dem;
struct Node{
	int v;
	int ls,rs;
	void clear(){ls=rs=0;}
}T[maxo];
int sz;
struct Point{
	ll pos[2];
	ll operator [] (const int &idx)const{return pos[idx];}
	void in(){scanf("%lld%lld",&pos[0],&pos[1]);}
}p[maxo];
int id[maxo];
#define sq(x) ((x)*(x))
ll dist(const Point &A,const Point &B){
	return sq(A[0]-B[0])+sq(A[1]-B[1]);
}
bool cmp(const int &a,const int &b){
	if(p[a][dem]!=p[b][dem]) return p[a][dem]<p[b][dem];
	return p[a][dem^1]<p[b][dem^1];
}
#define mi ((r+l)>>1)
int n;
void build(int &o,int l,int r,int w){ 
	if(l==r) return;
	dem=w;
	nth_element(id+l,id+mi,id+r,cmp);
	o=++sz;
	T[o].clear();
	T[o].v=id[mi];
	if(r-l==1) return;
	build(T[o].ls,l,mi,w^1);
	build(T[o].rs,mi+1,r,w^1);
}
ll ans;
Point qp;
void query(int o,int w){
	if(o==0) return;
	ll tmp=dist(p[T[o].v],qp);
	if(tmp) ans=min(ans,tmp);
	ll maxd=sq(p[T[o].v][w]-qp[w]);
	if(qp[w]<p[T[o].v][w]){
		query(T[o].ls,w^1);
		if(ans>=maxd) query(T[o].rs,w^1);
	}else{
		query(T[o].rs,w^1);
		if(ans>=maxd) query(T[o].ls,w^1);
	}
}
int root;
int Ts;
int main(){
	freopen("./in","r",stdin);
	cin>>Ts;
	while(Ts--){
		sz=0;
		cin>>n;
		for(int i=0;i<n;i++) p[i].in(),id[i]=i;
		build(root,0,n,0);
		for(int i=0;i<n;i++){
			qp=p[i];
			ans=1e18;
			query(root,0);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
