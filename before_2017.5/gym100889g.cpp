#include <bits/stdc++.h>

using namespace std;


typedef long long ll;
int T;
ll L,R,A,B;
ll dp[70][2][2][2][2];
ll DP(int p,int xu,int xl,int yu,int zu){
	if(p==-1) return 0;
	ll &ans=dp[p][xu][xl][yu][zu];
	if(ans!=-1) return ans;
	ans=0;
	ll bl=(L>>p)&1ll;
	ll br=(R>>p)&1ll;
	ll ba=(A>>p)&1ll;
	ll bb=(B>>p)&1ll;
	for(int i=(xl?bl:0);i<=(xu?br:1);i++){
		for(int j=0;j<=(yu?ba:1);j++){
			for(int k=0;k<=(zu?bb:1);k++){
				ll add=(i^j)+(i^k)+(j&k);
				add<<=p;
				int nxu=(xu&&(i==br));
				int nxl=(xl&&(i==bl));
				int nyu=(yu&&(j==ba));
				int nzu=(zu&&(k==bb));
				ans=max(ans,add+DP(p-1,nxu,nxl,nyu,nzu));
			}
		}
	}
	return ans;
}
int main(){
	freopen("/home/cwind/vimFile/in","r",stdin);
	cin>>T;
	while(T--){
		scanf("%lld%lld%lld%lld",&L,&R,&A,&B);
		memset(dp,-1,sizeof dp);
		printf("%lld\n",DP(62,1,1,1,1));
	}
	return 0;
}
