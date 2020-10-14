#include <bits/stdc++.h>

using namespace std;

const int maxn=2e5;
int n,m;
vector<int> G[maxn],T[maxn];
int end[maxn];
int a[maxn];
int d[maxn];
int vis[maxn];
void dfs(int v,int f,int t){
	vis[v]=1;
	int x=a[v];
	if(f!=0&&x!=f) d[f]++,T[x].push_back(f);
	if(x!=t&&t!=0) d[t]++,T[x].push_back(t);
	for(int i=0;i<G[v].size();i++){
		int u=G[v][i];
		dfs(u,x,end[v]?v:t);
	}
}
int ans[maxn],ah=0;
int cnt=0;
int main(){
	freopen("./in","r",stdin);
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		G[x].push_back(y);
	}
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),cnt+=end[a[i]]==0,end[a[i]]=1;
	for(int i=1;i<=n;i++){
		if(!vis[i]) dfs(i,0,0);
	}
	queue<int> Q;
	for(int i=1;i<=n;i++)
		if(end[i]&&d[i]==0) Q.push(i);
	while(!Q.empty()){
		int v=Q.front();
		ans[ah++]=v;
		Q.pop();
		for(int i=0;i<T[v].size();i++){
			int u=T[v][i];
			d[u]--;
			if(d[u]==0) Q.push(u);
		}
	}
	if(ah!=cnt) puts("-1");
	else{
		cout<<cnt<<endl;
		for(int i=0;i<ah;i++) printf("%d\n",ans[i]);
	}
	return 0;
}
