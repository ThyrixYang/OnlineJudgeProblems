#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxo=2e6;
const int maxn=3e5;
ll val[maxo];
ll lab[maxo];
int Max[maxo],Min[maxo];

#define ls ((o<<1))
#define rs ((o<<1)|1)
#define mi ((r+l)>>1)
void push_down(int o,int l,int r){
	if(r-l==1||!lab[o]) return;
	val[ls]=(mi-l)*lab[o];
	val[rs]=(r-mi)*lab[o];
	Min[ls]=Min[rs]=Max[ls]=Max[rs]=lab[ls]=lab[rs]=lab[o];
	lab[o]=0;
}
void push_up(int o){
	val[o]=val[ls]+val[rs];
	Max[o]=max(Max[ls],Max[rs]);
	Min[o]=min(Min[ls],Min[rs]);
}
ll n;
void build(int o,int l,int r){
	if(r-l==1){
		Max[o]=Min[o]=val[o]=l;
		return;
	}
	build(ls,l,mi);
	build(rs,mi,r);
	push_up(o);
}
void change(int o,int a,int b,int l,int r,ll x){
	if(a>=r||b<=l) return;
	push_down(o,l,r);
	if(l>=a&&r<=b){
		if(Max[o]<=x){
			Max[o]=Min[o]=lab[o]=x;
			val[o]=(r-l)*x;
			return;
		}
		if(Min[o]>=x) return;
	}
	change(ls,a,b,l,mi,x);
	change(rs,a,b,mi,r,x);
	push_up(o);
}
int a[maxn];
int D[maxn][4];
void add(int p,int x){
	for(int i=0;i<4;i++){
		if(D[p][i]==0){
			D[p][i]=x;
			return;
		}
	}
	D[p][2]=D[p][3];
	D[p][3]=x;
}
ll h[maxn];
int main(){
	freopen("./in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		for(int j=1;j*j<=a[i];j++){
			if(a[i]%j==0){
				add(j,i);
				if(j*j!=a[i]) add(a[i]/j,i);
			}
		}
	}
	build(1,1,n+1);
	ll ans=0;
	for(int v=2e5+1;v>=1;v--){
		if(D[v][0]==0){}
		else if(D[v][1]==0){}
		else if(D[v][2]==0){
			change(1,1,D[v][0]+1,1,n+1,D[v][0]);
			change(1,D[v][0]+1,D[v][1]+1,1,n+1,D[v][1]);
			change(1,D[v][1]+1,n+1,1,n+1,n+1);
		}else if(D[v][3]==0){
			change(1,1,D[v][0]+1,1,n+1,D[v][1]);
			change(1,D[v][0]+1,D[v][1]+1,1,n+1,D[v][2]);
			change(1,D[v][1]+1,n+1,1,n+1,n+1);
		}else{
			change(1,1,D[v][0]+1,1,n+1,D[v][2]);
			change(1,D[v][0]+1,D[v][1]+1,1,n+1,D[v][3]);
			change(1,D[v][1]+1,n+1,1,n+1,n+1);
		}
		h[v]=n*(n+1)-val[1];
	}
	for(int i=1;i<=2e5;i++) ans+=i*(h[i+1]-h[i]);
	cout<<ans<<endl;
	return 0;
}
