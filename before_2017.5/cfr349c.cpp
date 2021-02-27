#include<bits/stdc++.h>

using namespace std;

const int maxn=1e5+30000;
const long long mod=1e9+7;
long long qpow(long long a,long long p){
	long long ans=1;
	while(p>0){
		if(p&1) ans=ans*a%mod;
		a=a*a%mod;p>>=1;
	}
	return ans;
}
map<int,vector<int> > M;
long long p26[maxn],p25[maxn];
long long fac[maxn],inv[maxn];
long long inv26[maxn];
int getans(int n,int len){
	if(n<len) return 0;
	if(M.find(len)!=M.end()) return M[len][n-len]*p26[n]%mod;
	vector<int> ans;
	ans.push_back(inv26[len]);
	for(int i=1;i<=1e5;i++){
		long long tmp=ans.back();
		tmp+=fac[i+len-1]*inv[len-1]%mod*inv[i]%mod*inv26[len+i]%mod*p25[i]%mod;
		tmp%=mod;
		ans.push_back(tmp);
	}
	M[len]=ans;
	return ans[n-len]*p26[n]%mod;
}
int q;
char s[maxn];
int len;
int main(){
	freopen("./in","r",stdin);
	p26[0]=1,p25[0]=1,fac[0]=1;
	for(int i=1;i<maxn;i++) p26[i]=p26[i-1]*26%mod,p25[i]=p25[i-1]*25%mod;
	for(int i=1;i<maxn;i++) fac[i]=fac[i-1]*i%mod,inv[i]=qpow(fac[i],mod-2);
	for(int i=1;i<maxn;i++) inv26[i]=qpow(p26[i],mod-2);
	inv26[0]=inv[0]=1;
	cin>>q;
	scanf("%s",s);
	len=strlen(s);
	while(q--){
		int t;
		scanf("%d",&t);
		if(t==1){
			scanf("%s",s);
			len=strlen(s);
		}else{
			int n;
			scanf("%d",&n);
			cout<<getans(n,len)<<endl;
		}
	}
	return 0;
}
