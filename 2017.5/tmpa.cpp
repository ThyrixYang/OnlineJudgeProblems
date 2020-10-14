#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

typedef long long ll;

ll len[300];
ll cntb[300];
ll cal(int p,ll r){
	if(r==0) return 0;
	if(r==len[p]) return cntb[p];
	ll mid=len[p]>>1;
	if(r<=mid+1) return cal(p-1,min(r,mid))+(r==mid+1);
	ll ans=cntb[p-1]+1;
	ll nd=cal(p-1,len[p]-r);
	ll td=cntb[p-1];
	ll tb=len[p-1]-td;
	ll nb=len[p]-r-nd;
	ans+=tb-nb;
	return ans;
}
ll T,a,b;
int main(){
	freopen("./in","r",stdin);
	len[1]=1;
	cntb[1]=1;
	for(int i=2;i<=200;i++){
		len[i]=len[i-1]*2+1;
		cntb[i]=cntb[i-1]+1+len[i-1]-cntb[i-1];
	}
	cin>>T;
	while(T--){
		cin>>a>>b;
		int h=1;
		while(len[h]<b) h++;
		cout<<cal(h,b)-cal(h,a-1)<<endl;
	}
	return 0;
}
