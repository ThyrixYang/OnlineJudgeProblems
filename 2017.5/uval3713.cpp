#include <bits/stdc++.h>

using namespace std;

#define pb push_back
const int maxn=2e5+30000;
vector<int> G[maxn],rG[maxn];
void addedge(int x,int y){
	G[x].pb(y);
	rG[y].pb(x);
}
int n,m;
int a[maxn];
bool old[maxn];
int vis[maxn];
vector<int> od;
void dfs1(int v){
	vis[v]=1;
	for(int i=0;i<G[v].size();i++) if(!vis[G[v][i]]) dfs1(G[v][i]);
	od.pb(v);
}
void dfs2(int v,int k){
	vis[v]=k;
	for(int i=0;i<rG[v].size();i++) if(!vis[rG[v][i]]) dfs2(rG[v][i],k);
}
void scc(){
	memset(vis,0,sizeof vis);
	od.clear();
	for(int i=1;i<=n;i++)
		if(!vis[i]) dfs1(i);
	memset(vis,0,sizeof vis);
	int k=1;
	for(int i=od.size()-1;i>=0;i--){
		int v=od[i];
		if(!vis[v]) dfs2(v,k++);
	}
}
void init(){
	for(int i=0;i<=2*n;i++) G[i].clear(),rG[i].clear(),old[i]=0;
}
int ans[maxn];
int main(){
	freopen("./in","r",stdin);
	while(cin>>n>>m){
		if(n==0&&m==0) break;
		init();
		int suma=0;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),suma+=a[i];
		int lim=suma/n;
		if(suma%n) lim++;
		for(int i=1;i<=n;i++) if(a[i]>=lim) old[i]=1;
		for(int i=0;i<m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			if(old[x]&&old[y]){
				addedge(x,y+n);
				addedge(y,x+n);
				addedge(y+n,x);
				addedge(x+n,y);
			}else if(old[x]&&!old[y]){
				addedge(x+n,y);
				addedge(y+n,x);
			}else if(!old[x]&&old[y]){
				addedge(x+n,y);
				addedge(y+n,x);
			}else{
				addedge(x,y+n);
				addedge(y,x+n);
				addedge(y+n,x);
				addedge(x+n,y);
			}
		}
		scc();
		int f=1;
		for(int i=1;i<=n;i++){
			if(vis[i]==vis[i+n]){
				f=-1;
				break;
			}else{
				if(vis[i]>vis[i+n]) ans[i]=1;
				else ans[i]=0;
			}
		}
		if(f==-1) puts("No solution.");
		else{
			for(int i=1;i<=n;i++){
				if(ans[i]){
					if(old[i]) puts("A");
					else puts("B");
				}else{
					puts("C");
				}
			}
		}
	}
	return 0;
}
