#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
const int maxn=2e6;
const int maxv=4e5;
const long long INF=3e14+333;
struct Node{
	int u,v,c;
	void in(){scanf("%d%d%d",&u,&v,&c);}
}wo[maxn];
vector<int> G[maxv],st[maxv],ed[maxv];
int n,m;
int dfn=0;
int d[maxv][2];
int wd[maxv];
void dfs(int v,int f){
	d[v][0]=dfn;
	for(int i=0;i<G[v].size();i++){
		int u=G[v][i];
		if(u==f) continue;
		dfs(u,v);
	}
	for(int i=0;i<st[v].size();i++)
		wd[st[v][i]]=dfn++;
	d[v][1]=dfn;
}
ull dp[maxn];
ull val[maxn],add[maxn];
#define ls ((o<<1))
#define rs ((o<<1)|1)
#define mi ((r+l)>>1)
void push(int o,int l,int r){
	if(r-l<=1||!add[o]) return ;
	val[ls]+=add[o];val[rs]+=add[o];
	add[ls]+=add[o];add[rs]+=add[o];
	add[o]=0;
}
void change(int o,int p,int l,int r,ull x){
	push(o,l,r);
	if(r-l<=1){
		val[o]=x;
		return ;
	}
	if(p<mi) change(ls,p,l,mi,x);
	else change(rs,p,mi,r,x);
	val[o]=min(val[ls],val[rs]);
}
void Add(int o,int a,int b,int l,int r,ull x){
	if(a>=r||b<=l) return;
	push(o,l,r);
	if(l>=a&&r<=b){
		val[o]+=x;
		add[o]+=x;
		return;
	}
	Add(ls,a,b,l,mi,x);
	Add(rs,a,b,mi,r,x);
	val[o]=min(val[ls],val[rs]);
}
ull rmq(int o,int a,int b,int l,int r){
	if(a>=r||b<=l) return INF;
	push(o,l,r);
	if(l>=a&&r<=b) return val[o];
	return min(rmq(ls,a,b,l,mi),rmq(rs,a,b,mi,r));
}
ull ans=0;
void DP(int v,int f){
	ull sum=0;
	for(int i=0;i<G[v].size();i++){
		int u=G[v][i];
		if(u==f) continue;
		DP(u,v);
		sum+=dp[u];
	}
	for(int i=0;i<G[v].size();i++){
		int u=G[v][i];
		if(u==f) continue;
		Add(1,d[u][0],d[u][1],0,m,sum-dp[u]);
	}
	for(int i=0;i<st[v].size();i++){
		int w=st[v][i];
		change(1,wd[w],0,m,sum+wo[w].c);
	}
	for(int i=0;i<ed[v].size();i++){
		int w=ed[v][i];
		change(1,wd[w],0,m,INF);
	}
	if(v==1) ans=sum;
	dp[v]=rmq(1,d[v][0],d[v][1],0,m);
}
int main(){
	freopen("./in","r",stdin);
	cin>>n>>m;
	for(int i=0;i<n-1;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for(int i=0;i<m;i++){
		wo[i].in();
		st[wo[i].u].push_back(i);
		ed[wo[i].v].push_back(i);
	}
	for(int i=0;i<m;i++) change(1,i,0,m,INF);
	dfs(1,-1);
	DP(1,-1);
	if(ans>=INF) cout<<-1<<endl;
	else cout<<ans<<endl;
	return 0;
}
