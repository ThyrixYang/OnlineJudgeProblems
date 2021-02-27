#include <bits/stdc++.h>

using namespace std;

const int maxn=1e6+3000;
int n,k;
int a[maxn];
int b[maxn];
int bi[maxn];
int ch[maxn*30][2];
int cnt[maxn*30];
int sz=0;
void getBit(int x){
	for(int i=30;i>=0;i--) bi[i]=(x>>i)&1;
}
void insert(){
	int v=0;
	for(int i=30;i>=0;i--){
		if(ch[v][bi[i]]==0)
			ch[v][bi[i]]=++sz;
		v=ch[v][bi[i]];
		cnt[v]++;
	}
}
long long Count(int v,int b,int val){
	if(v==0&&b!=30||b<0) return 0;
	//cout<<v<<" "<<b<<" "<<val<<endl;
	long long ans=0;
	int next=ch[v][1];
	if(val+((bi[b]^1)<<b)>=k) ans+=cnt[next];
	else if(val+((bi[b]^1)<<b)+(1<<b)-1>=k&&cnt[next]) ans+=Count(next,b-1,val+((bi[b]^1)<<b));
	next=ch[v][0];
	if(val+(bi[b]<<b)>=k) ans+=cnt[next];
	else if(val+(bi[b]<<b)+(1<<b)-1>=k&&cnt[next]) ans+=Count(next,b-1,val+(bi[b]<<b));
	return ans;
}
int main(){
	freopen("./in","r",stdin);
	cin>>n>>k;
	long long ans=0;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=b[i-1]^a[i];
	for(int i=1;i<=n+1;i++){
		getBit(b[i]);
		ans+=Count(0,30,0);
		insert();
	}
	cout<<ans<<endl;
	return 0;
}
