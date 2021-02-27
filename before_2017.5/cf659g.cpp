#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod=1e9+7;
const int maxn=1e6+3000;
ll h[maxn];
ll a[maxn];
int n;
#define sq(x) ((x)*(x))
int main(){
	freopen("/home/cwind/vimFile/in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%lld",&h[i]);
	ll ans=0;
	for(int i=1;i<=n;i++) ans=(ans+h[i]-1)%mod;
	for(int i=1;i<=n;i++){
		ans+=a[i-1]*(min(h[i-1],h[i])-1)%mod;
		ans%=mod;
		a[i]=a[i-1]*(min(min(h[i-1],h[i]),h[i+1])-1)%mod;
		a[i]+=min(h[i],h[i+1])-1;
		a[i]%=mod;
	}
	cout<<ans<<endl;
	return 0;
}
