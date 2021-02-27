#include<bits/stdc++.h>
using namespace std;
const int maxn=600;
int n,m,p;
vector<int> G[maxn];
char s[maxn][2][20];
int match[maxn];
bool vis[maxn];
bool dfs(int v){
	vis[v]=1;
	for(int i=0;i<G[v].size();i++){
		int u=G[v][i];
		int w=match[u];
		if(w==-1||!vis[w]&&dfs(w)){
			match[u]=v;
			match[v]=u;
			return 1;
		}
	}
	return 0;
}
int bi_match(){
	memset(match,-1,sizeof match);
	int ans=0;
	for(int i=1;i<=p;i++){
		if(match[i]==-1){
			memset(vis,0,sizeof vis);
			if(dfs(i)) ans++;
		}
	}
	return ans;
}
#define pb push_back
int main(){
	freopen("/home/slyfc/vimFile/in","r",stdin);
	while(cin>>n>>m>>p){
		for(int i=1;i<=p;i++){
			scanf("%s%s",s[i][0],s[i][1]);
		}
		for(int i=0;i<=p;i++) G[i].clear();
		for(int i=1;i<=p;i++){
			for(int j=1;j<=p;j++){
				if(strcmp(s[i][0],s[j][1])==0||
						strcmp(s[i][1],s[j][0])==0)
					G[i].pb(j),G[j].pb(i);
			}
		}
		printf("%d\n",p-bi_match());
	}
	return 0;
}
