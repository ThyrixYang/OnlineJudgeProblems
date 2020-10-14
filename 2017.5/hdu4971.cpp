#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>
#include <vector>
#define INF (0x3f3f3f3f)
using namespace std;


const int MAXV=2000+30000;
const int MAXE=3e6;
struct EDGE{
	int to,cap,next;
	EDGE(int to=0,int cap=0,int next=0):to(to),cap(cap),next(next){}
}E[MAXE];
int eh;
int d[MAXV],gap[MAXV],head[MAXV];
int Sink,Source;
int V;
void addedge(int from,int to,int cap){///注意边的方向
	E[eh]=EDGE(to,cap,head[from]);
	head[from]=eh++;
	E[eh]=EDGE(from,0,head[to]);///反相边的流量
	head[to]=eh++;
}
void isap_init(){//注意点数
	eh=0;
	memset(gap,0,sizeof gap);
	memset(d,0,sizeof d);
	memset(head,-1,sizeof head);
}
int vis[MAXV];
int Q[MAXE],front,back;
void bfs(){
	memset(vis,0,sizeof vis);
	front=back=0;
	vis[Sink]=1;
	Q[back++]=Sink;
	while(front<back){
		int v=Q[front++];
		for(int i=head[v];i!=-1;i=E[i].next){
			int u=E[i].to;
			if(!vis[u]){
				++gap[d[u]=d[v]+1];
				vis[u]=1;
				Q[back++]=u;
			}
		}
	}
}
int dfs(int v,int f){
	if(v==Sink) return f;
	int tmp=0,minh=V;
	for(int i=head[v];i!=-1;i=E[i].next){
		int u=E[i].to,c=E[i].cap;
		if(!c) continue;
		if(d[v]==d[u]+1){
			int a=dfs(u,min(f,c));
			E[i].cap-=a,E[i^1].cap+=a;
			tmp+=a,f-=a;
			if(!f) break;
			if(d[Source]>=V) return tmp;
		}
		if(E[i].cap) minh=min(d[u],minh);
	}
	if(!tmp){
		if(--gap[d[v]]==0) d[Source]=V;
		++gap[d[v]=minh+1];
	}
	return tmp;
}
int isap(int s,int t,int cntv){
	V=cntv;
	Source=s,Sink=t;
	bfs();
	int flow=0;
	while(d[s]<V) flow+=dfs(s,INF);
	return flow;
}


int T,n,m;
int cas=0;
int main(){
	freopen("/home/slyfc/vimFile/in","r",stdin);
	cin>>T;
	while(T--){
		isap_init();
		cin>>n>>m;
		int s=0,t=n+m+1;
		int sum=0;
		for(int i=1;i<=n;i++){
			int x;
			scanf("%d",&x);
			addedge(s,i,x);
			sum+=x;
		}
		for(int i=1;i<=m;i++){
			int x;
			scanf("%d",&x);
			addedge(i+n,t,x);
		}
		for(int i=1;i<=n;i++){
			int k;
			scanf("%d",&k);
			for(int j=0;j<k;j++){
				int x;
				scanf("%d",&x);
				x++;
				addedge(i,n+x,INF);
			}
		}
		for(int i=1;i<=m;i++){
			for(int j=1;j<=m;j++){
				int x;
				scanf("%d",&x);
				if(x==1) addedge(i+n,j+n,INF);
			}
		}
		int res=sum-isap(s,t,n+m+2);
		printf("Case #%d: ",++cas);
		printf("%d\n",res);
	}
	return 0;
}
