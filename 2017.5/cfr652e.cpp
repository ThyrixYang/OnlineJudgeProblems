#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define se second
#define fs first
typedef pair<int,int> P;
const int maxn=1e6;
vector<P> G[maxn],T[maxn];
int st,ed;
int n,m;
int id[maxn];
int cnt=0;
int low[maxn],od[maxn];
int stk[maxn],top=0;
int clo=1;
int has[maxn];
void dfs(int v,int f){
	od[v]=low[v]=clo++;
	stk[top++]=v;
	for(int i=0;i<G[v].size();i++){
		int u=G[v][i].fs;
		if(u==f) continue;
		if(!od[u]){
			dfs(u,v);
			low[v]=min(low[v],low[u]);
			if(low[u]==od[u]){
				cnt++;
				do{
					id[stk[--top]]=cnt;
				}while(stk[top]!=u);
			}
		}
		else low[v]=min(od[u],low[v]);
	}
}
void build(){
	for(int i=1;i<=n;i++){
		for(int j=0;j<G[i].size();j++){
			int v=i,u=G[i][j].fs;
			if(v<u) continue;
			int w=G[i][j].se;
			if(id[v]==id[u]){
				if(w) has[id[v]]=1;
			}else{
				T[id[v]].pb(P(id[u],w));
				T[id[u]].pb(P(id[v],w));
			}
		}
	}
}
bool dfsx(int v,int f,int x){
	x|=has[v];
	if(v==ed) return x;
	for(int i=0;i<T[v].size();i++){
		int u=T[v][i].fs,w=T[v][i].se;
		if(u==f) continue;
		if(dfsx(u,v,x|w)) return 1;
	}
	return 0;
}
int main(){
	freopen("./in","r",stdin);
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		G[x].pb(P(y,z));
		G[y].pb(P(x,z));
	}
	scanf("%d%d",&st,&ed);
	dfs(st,-1);
	cnt++;
	while(top>0) id[stk[--top]]=cnt;
	build();
	if(id[st]==id[ed]){
		if(has[id[st]]) puts("YES");
		else puts("NO");
	}else{
		st=id[st];
		ed=id[ed];
		if(dfsx(st,-1,0)) puts("YES");
		else puts("NO");
	}
	return 0;
}
