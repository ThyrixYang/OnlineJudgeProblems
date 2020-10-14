#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int state=60000;
int n,a,b,q;
ll t;
ll dp[11][state][11];
int ans[20][20];
bool ok[state];
int p3[30];
int bt[11];
int change[state][11][3];
int getbt[state][11];
void get(int x){
	for(int i=0;i<n;i++){
		bt[i]=x%3;
		x/=3;
	}
}
int rget(){
	int ans=0;
	for(int i=0;i<n;i++){
		ans+=p3[i]*bt[i];
	}
	return ans;
}
void init(){
	p3[0]=1;
	for(int i=1;i<=n;i++) p3[i]=p3[i-1]*3;
	for(int i=0;i<state;i++){
		bool f=1;
		get(i);
		for(int j=0;j<n;j++){
			getbt[i][j]=bt[j];
			if(bt[j]==0) f=0;
		}
		ok[i]=f;
	}
	for(int i=0;i<state;i++){
		for(int j=0;j<n;j++){
			get(i);
			for(int k=0;k<3;k++){
				bt[j]=k;
				change[i][j][k]=rget();
			}
		}
	}
}
ll cnt(int r,int s,int cnt1,int p){
	if(r==n) return ok[s];
	if(p==n){
		if(cnt1>=a&&cnt1<=b) return cnt(r+1,s,0,0);
		else return 0;
	}
	ll &ans=dp[r][s][p];
	if(ans!=-1) return ans;
	ans=0;
	int up=getbt[s][p];
	int s1=change[s][p][0];
	int s2=change[s][p][1];
	int s3=change[s][p][2];
	if(up==0){
		ans+=cnt(r,s1,cnt1,p+1);
		ans+=cnt(r,s2,cnt1+1,p+1);
	}else if(up==1){
		ans+=cnt(r,s2,cnt1+1,p+1);
		ans+=cnt(r,s3,cnt1,p+1);
	}else
		ans+=cnt(r,s3,cnt1,p+1);
	return ans;
}
bool getans(int r,int s,int cnt1,int p,ll k){
	if(r==n){
		if(k==1) return 1;
		return 0;
	}
	if(p==n){
		if(cnt1>=a&&cnt1<=b)
			return getans(r+1,s,0,0,k);
		else 
			return 0;
	}
	int up=getbt[s][p];
	int s1=change[s][p][0];
	int s2=change[s][p][1];
	int s3=change[s][p][2];
	if(up==0){
		ll x1=cnt(r,s1,cnt1,p+1);
		if(x1>=k){
			ans[r][p]=0;
			return getans(r,s1,cnt1,p+1,k);
		}else{
			ans[r][p]=1;
			return getans(r,s2,cnt1+1,p+1,k-x1);
		}
	}else if(up==1){
		ll x1=cnt(r,s3,cnt1,p+1);
		if(x1>=k){
			ans[r][p]=0;
			return getans(r,s3,cnt1,p+1,k);
		}else{
			ans[r][p]=1;
			return getans(r,s2,cnt1+1,p+1,k-x1);
		}
	}else{
		ans[r][p]=0;
		return getans(r,s3,cnt1,p+1,k);
	}
}
int main(){
	freopen("/home/cwind/vimFile/in","r",stdin);
	cin>>n>>a>>b>>q;
	init();
	memset(dp,-1,sizeof dp);
	while(q--){
		scanf("%lld",&t);
		bool res=getans(0,0,0,0,t);
		if(!res) puts("No such matrix.");
		else{
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					printf("%d",ans[i][j]);
				}
				puts("");
			}
		}
		if(q) puts("");
	}
	return 0;
}
