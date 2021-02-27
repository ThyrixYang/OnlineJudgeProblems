#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define INF (0x3f3f3f3f)
const int MAXV=1200;
const int MAXE=1000000;
struct EDGE{
    int to,cap,next;
}ES[MAXE];
int head[MAXV];
int eh;
void addedge(int from,int to,int cap){///加边
    ES[eh].to=to,ES[eh].cap=cap,ES[eh].next=head[from];
    head[from]=eh++;
    ES[eh].to=from,ES[eh].cap=0,ES[eh].next=head[to];
    head[to]=eh++;
}
int level[MAXV];
queue<int> Q;
void bfs(int s){////bfs出分层图
    memset(level,-1,sizeof level);
    level[s]=0;
    Q.push(s);
    while(!Q.empty()){
        int v=Q.front();Q.pop();
        for(int i=head[v];i!=-1;i=ES[i].next){
            EDGE &e=ES[i];
            if(e.cap>0&&level[e.to]==-1){
                level[e.to]=level[v]+1;
                Q.push(e.to);
            }
        }
    }
}
int iter[MAXV];
int dfs(int v,int t,int f){///dfs寻找增广路径
    if(v==t) return f;
    for(int &i=iter[v];i!=-1;i=ES[i].next){
        EDGE &e=ES[i];
        if(e.cap>0&&level[e.to]>level[v]){
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0){
                e.cap-=d;
                ES[i^1].cap+=d;
                return d;
            }
        }
    }
    return 0;
}
int dinic(int s,int t){///dinic算法求解最大流
    int flow=0;
    for(;;){
        bfs(s);
        if(level[t]==-1) return flow;
        for(int i=0;i<MAXV;i++) iter[i]=head[i];
        int f;
        while((f=dfs(s,t,INF))>0) flow+=f;
    }
    return 0;
}
void dinic_init(){
    memset(head,-1,sizeof head);
    eh=0;
}

const int maxn=10005;
int T;
int n,m,f;
int fa[maxn];
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
vector<int> G[maxn];
void build(int mid){
	dinic_init();
	int s=0,t=2*n+1;
	for(int i=1;i<=n;i++) addedge(s,i,mid),addedge(i+n,t,mid);
	for(int i=1;i<=n;i++){
		int x=find(i);
		for(int j=0;j<G[x].size();j++)
			addedge(i,G[x][j]+n,1);
	}
}
void solve(){
	int l=0,r=n+1;
	while(r-l>1){
		int mid=(r+l)>>1;
		build(mid);
		int s=0,t=2*n+1;
		int res=dinic(s,t);
		if(res==mid*n) l=mid;
		else r=mid;
	}
	printf("%d\n",l);
}
int s[maxn][2];
int main(){
	freopen("/home/slyfc/vimFile/in","r",stdin);
	cin>>T;
	while(T--){
		cin>>n>>m>>f;
		for(int i=0;i<maxn;i++) fa[i]=i,G[i].clear();
		for(int i=0;i<m;i++) scanf("%d%d",&s[i][0],&s[i][1]);
		for(int i=m;i<m+f;i++) {
			scanf("%d%d",&s[i][0],&s[i][1]);
			fa[find(s[i][0])]=find(s[i][1]);
		}
		for(int i=0;i<m;i++)
			G[find(s[i][0])].pb(s[i][1]);
		for(int i=1;i<=n;i++){
			sort(G[i].begin(),G[i].end());
			G[i].erase(unique(G[i].begin(),G[i].end()),G[i].end());
		}
		solve();
	}
	return 0;
}
