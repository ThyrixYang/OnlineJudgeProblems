//保证没有重复的集合统计？


#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod=1e9+7;
ll qpow(ll a,ll p){
	ll ans=1;
	while(p>0){
		if(p&1) ans=(ans*a)%mod;
		a=a*a%mod;p>>=1;
	}
	return ans;
}
int n,m;
int main(){
	freopen("/home/cwind/vimFile/in","r",stdin);
	cin>>n>>m;
	if(m==1){
		cout<<n+1<<endl;
		return 0;
	}
	ll ans=qpow(m,n)+m*qpow(m-1,mod-2)%mod*(qpow(2*m-1,n)-qpow(m,n)+mod)%mod;
	ans%=mod;
	cout<<ans<<endl;
	return 0;
}
