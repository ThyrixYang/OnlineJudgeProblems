#include<cstdio>
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=1005;
bool a[maxn][maxn];
vector<int> G[maxn];
int n,m;
int match[maxn];
int vis[maxn];
bool dfs(int v){
	vis[v]=1;
	for(int i=0;i<G[v].size();i++){
		int u=G[v][i];
		if(vis[u]) continue;
		int w=match[u];
		if(w==-1||!vis[w]&&dfs(w)){
			match[v]=u;
			match[u]=v;
			return 1;
		}
	}
	return 0;
}
int bi_match(){
	int ans=0;
	memset(match,-1,sizeof match);
	for(int i=1;i<=n;i++){
		if(match[i]==-1){
			memset(vis,0,sizeof vis);
			if(dfs(i)) ans++;
		}
	}
	return ans;
}
int main(){
	while(cin>>n>>m,n){
		memset(a,0,sizeof a);
		for(int i=0;i<m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			a[x][y]=1;
		}
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					a[i][j]|=(a[i][k]&a[k][j]);
		for(int i=n+1;i<=n*2;i++) G[i].clear();
		for(int i=1;i<=n;i++){
			G[i].clear();
			for(int j=1;j<=n;j++) if(a[i][j])
				G[i].push_back(j+n),G[j+n].push_back(i);
		}
		printf("%d\n",n-bi_match());
	}
	return 0;
}
