#include <bits/stdc++.h>

using namespace std;

const int maxn=2e6;
typedef pair<int,int> P;
P val[maxn];
#define ls ((o<<1))
#define rs ((o<<1)|1)
#define mi ((r+l)>>1)
void update(int o,int p,int l,int r,P x){
	if(r-l<=1){
		val[o]=x;
		return;
	}
	val[o]=max(val[o],x);
	if(p<mi) update(ls,p,l,mi,x);
	else update(rs,p,mi,r,x);
}
P rmq(int o,int a,int b,int l,int r){
	if(a>=r||b<=l) return P(0,0);
	if(l>=a&&r<=b) return val[o];
	return max(rmq(ls,a,b,l,mi),rmq(rs,a,b,mi,r));
}
long long dp[maxn];
int n;
int a[maxn];
int main(){
	freopen("./in","r",stdin);
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>a[i];
		update(1,i,1,n+1,P(a[i],i));
	}
	a[n]=n;
	update(1,n,1,n+1,P(n,n));
	long long ans=0;
	for(int i=n-1;i>=1;i--){
		P res=rmq(1,i+1,a[i]+1,1,n+1);
		int m=res.second;
		dp[i]=dp[m]-(a[i]-m)+n-i;
		ans+=dp[i];
	}
	cout<<ans<<endl;
	return 0;
}
