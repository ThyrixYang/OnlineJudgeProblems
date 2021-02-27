#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn=3e5;
ll a[maxn],sum[maxn];
struct Line{
	ll a,b;
	Line(ll a=0,ll b=0):a(a),b(b){}
	ll get(ll x){return a*x+b;}
};
Line stk[maxn];
ll top;
int n;
void clear(){top=0;}
void addLine(ll a,ll b){
	for(;;){
		if(top<=1) break;
		Line &l1=stk[top-2],&l2=stk[top-1];
		if((b-l1.b)*(l2.a-l1.a)>=(a-l1.a)*(l2.b-l1.b)) top--;
		else break;
	}
	stk[top++]=Line(a,b);
}
ll getVal(ll x){
	ll l=-1,r=top-1;
	while(r-l>1){
		ll mid=(r+l)>>1;
		if(stk[mid].get(x)>=stk[mid+1].get(x)) r=mid;
		else l=mid;
	}
	return stk[r].get(x);
}
ll ans=0;
ll maxc=0;
int main(){
	freopen("./in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) ans+=a[i]*i,sum[i]=sum[i-1]+a[i];
	clear();
	for(int i=n-1;i>=1;i--){
		addLine(-(i+1),-sum[i+1]);
		maxc=max(maxc,getVal(-a[i])+sum[i]-i*a[i]);
	}
	clear();
	for(int i=2;i<=n;i++){
		addLine(i-1,-sum[i-2]);
		maxc=max(maxc,getVal(a[i])+sum[i-1]-i*a[i]);
	}
	cout<<ans+maxc<<endl;
	return 0;
}
