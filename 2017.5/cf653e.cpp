#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> P;
const int maxn=5e5;
set<P> S;
int cvis=0;
int n,m,k;
int fa[maxn];
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void dfs(int v){
	cvis++;
	fa[v]=find(v+1);
	for(int i=find(1);i<=n;i=find(i+1)){
		if(S.find(P(v,i))==S.end()) dfs(i);
	}
}
int cnt[maxn];
int main(){
	freopen("./in","r",stdin);
	cin>>n>>m>>k;
	for(int i=1;i<=n+1;i++) fa[i]=i;
	int cnt1=n-1;
	int cnt2=0;
	for(int i=0;i<m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		if(x>y) swap(x,y);
		if(x!=1) cnt[y]++,cnt[x]++;
		if(cnt[x]==n-1) cnt2++;
		if(cnt[y]==n-1) cnt2++;
		if(x==1) cnt1--;
		S.insert(P(x,y));
		S.insert(P(y,x));
	}
	dfs(1);
	if(cnt1<k||cnt2>k||cvis!=n){
		puts("impossible");
	}else{
		puts("possible");
	}
	return 0;
}
