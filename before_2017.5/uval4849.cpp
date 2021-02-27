#include <bits/stdc++.h>

using namespace std;

int T,n,m;
#define pb push_back
struct TwoSet{
	static const int maxn=6005;
	vector<int> G[maxn],rG[maxn];
	vector<int> od;
	int vis[maxn];
	void addedge(int x,int y){
		G[x].pb(y);
		G[y].pb(x);
	}
	void clear(){
		for(int i=0;i<maxn;i++) G[i].clear(),rG[i].clear();
		od.clear();
	}
	void dfs(int v){
		vis[v]=1;
		for(int i=0;i<G[v].size();i++) if(!vis[G[v][i]]) dfs(G[v][i]);
		od.pb(v);
	}
	void rdfs(int v,int k){
		vis[v]=k;
		for(int i=0;i<rG[v].size();i++) if(!vis[rG[v][i]]) rdfs(rG[v][i],k);
	}
	bool solve(){
		memset(vis,0,sizeof vis);
		for(int i=1;i<=n*2;i++) if(!vis[i]) dfs(i);
		memset(vis,0,sizeof vis);
		int k=1;
		for(int i=od.size()-1;i>=0;i--) if(!vis[i]) rdfs(i,k++);
		for(int i=1;i<=n;i++) if(vis[i]==vis[i+n]) return 0;
		return 1;
	}
}Set;
const int maxn=3005;
int x[maxn],y[maxn];
int p[maxn][2][2];
vector<int> G[maxn];
int dist(int i,int ii,int j,int jj){
	return abs(p[i][ii][0]-p[j][jj][0])+abs(p[i][ii][1]-p[j][jj][1]);
}
int col[maxn];
bool color(int v,int c){
	for(int i=0;i<G[v].size();i++){
		int u=G[v][i];
		int c1=dist(
	}
}
bool check(int v,int c){
	memset(col,-1,sizeof col);
	if(!color(v,c)) return 0;
	Set.clear();
	for(int i=1;i<=n;i++){
		if(col[i]!=-1){
			if(col[i]==0){
				p[i][0][0]=x[i],p[i][0][1]=y[i];
				p[i][1][0]=x[i]+1,p[i][1][1]=y[i]+1;
			}else{
				p[i][0][0]=x[i]+1,p[i][0][1]=y[i];
				p[i][1][0]=x[i],p[i][1][1]=y[i]+1;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(col[i]==-1) continue;
		for(int j=0;j<G[i].size();j++){
			int to=G[i][j];
			int d1=dist(i,0,j,0);
			int d2=dist(i,0,j,1);
			if(!d1||!d2){
			}
			d1=dist(i,1,j,0);
			d2=dist(i,1,j,1);
			if(!d1||!d2){
			}
		}
	}
	return Set.solve();
}
int fa[maxn];
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
int main(){
	freopen("./in","r",stdin);
	cin>>T;
	while(T--){
		scanf("%d",&n);
		for(int i=0;i<=n;i++) G[i].clear(),fa[i]=i;
		for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
		scanf("%d",&m);
		for(int i=0;i<m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			G[x].pb(y);
			G[y].pb(x);
			fa[find(x)]=find(y);
		}
		int f=1;
		for(int i=1;i<=n;i++){
			if(find(i)==i){
				if(!check(i,1)&&!check(i,0)){
					f=-1;
					break;
				}
			}
		}
		if(f==1) puts("possible");
		else puts("impossible");
	}
	return 0;
}
