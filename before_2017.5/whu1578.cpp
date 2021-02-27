#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod=1e9+7;
#define pb push_back
const int maxn=1e5+3000;
int l[maxn],r[maxn];
int n,m;
int a[maxn];
int cnt[maxn];
vector<int> buk[2000];
int q[maxn],qh;
bool cmp(int a,int b){
	return r[a]<r[b];
}
int res;
ll ans;
void add(int x){
	res++;
	if(cnt[x-1]>cnt[x]) res--;
	if(cnt[x+1]>cnt[x]) res--;
	cnt[x]++;
}
void del(int x){
	if(cnt[x]>cnt[x-1]&&cnt[x]>cnt[x+1]) res--;
	if(cnt[x]<=cnt[x-1]&&cnt[x]<=cnt[x+1]) res++;
	cnt[x]--;
}
int main(){
	freopen("/home/cwind/vimFile/in","r",stdin);
	while(cin>>n>>m){
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=m;i++) scanf("%d%d",&l[i],&r[i]);
		int sz=1;
		while(sz*sz<n) sz++;
		int di=n/sz;
		for(int i=0;i<=di;i++) buk[i].clear();
		for(int i=1;i<=m;i++) buk[l[i]/sz].pb(i);
		for(int i=0;i<=di;i++) sort(buk[i].begin(),buk[i].end(),cmp);
		qh=0;
		for(int i=0;i<=di;i++){
			if(i%2)
				for(int j=0;j<buk[i].size();j++) q[qh++]=buk[i][j];
			else 
				for(int j=buk[i].size()-1;j>=0;j--) q[qh++]=buk[i][j];
		}
		int x=1,y=1;
		memset(cnt,0,sizeof cnt);
		cnt[a[1]]=1;
		res=1;
		ans=1;
		for(int i=0;i<m;i++){
			for(int j=y+1;j<=r[q[i]];j++) add(a[j]);
			for(int j=x-1;j>=l[q[i]];j--) add(a[j]);
			for(int j=x;j<l[q[i]];j++) del(a[j]);
			for(int j=y;j>r[q[i]];j--) del(a[j]);
			ans=(ans*res)%mod;
			x=l[q[i]],y=r[q[i]];
		}
		cout<<ans<<endl;
	}
	return 0;
}
