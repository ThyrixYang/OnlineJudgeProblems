#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <utility>
#include <cstdio>
#define INF (0x3f3f3f3f)
using namespace std;

const double eps=1e-7;
const int maxv=120;
const int maxe=1e6;
struct EDGE{
	int to,next;
	double cap;
	EDGE(int to=0,double cap=0,int next=-1):to(to),cap(cap),next(next){}
}E[maxe];
int head[maxv];
int eh;
void init(){
	memset(head,-1,sizeof head);
	eh=0;
}
void addedge(int from,int to,double cap){
	E[eh]=EDGE(to,cap,head[from]);
	head[from]=eh++;
	E[eh]=EDGE(from,0,head[to]);
	head[to]=eh++;
}
int level[maxv];
int Q[maxe],front,back;
void bfs(int s){
	memset(level,-1,sizeof level);
	level[s]=0;
	front=back=0;
	Q[back++]=s;
	while(front<back){
		int v=Q[front++];
		for(int i=head[v];i!=-1;i=E[i].next){
			EDGE &e=E[i];
			if(e.cap>0&&level[e.to]==-1){
				level[e.to]=level[v]+1;
				Q[back++]=e.to;
			}
		}
	}
}
int s,t;
int iter[maxv];
double dfs(int v,double f){
	if(v==t) return f;
	for(int &i=iter[v];i!=-1;i=E[i].next){
		EDGE &e=E[i];
		if(e.cap==0||level[e.to]!=level[v]+1) continue;
		double d=dfs(e.to,min(e.cap,f));
		if(d>eps){
			e.cap-=d,E[i^1].cap+=d;
			return d;
		}
	}
	return 0;
}
double maxFlow(){
	double flow=0;
	for(;;){
		bfs(s);
		if(level[t]==-1) return flow;
		double d;
		for(int i=0;i<maxv;i++) iter[i]=head[i];
		while((d=dfs(s,INF))>0) flow+=d;
	}
}

int n,m;
double U;
int es[2000][2];
int deg[maxv];
void build(double rate){
	init();
	int s=0,t=n+1;
	for(int i=0;i<m;i++){
		addedge(es[i][0],es[i][1],1);
		addedge(es[i][1],es[i][0],1);
	}
	for(int i=1;i<=n;i++) addedge(s,i,U);
	for(int i=1;i<=n;i++) addedge(i,t,U+rate*2-deg[i]);
}
bool vis[maxv];
void dfs(int v){
	vis[v]=1;
	for(int i=head[v];i!=-1;i=E[i].next){
		EDGE &e=E[i];
		if(e.cap>eps&&!vis[e.to]) dfs(e.to);
	}
}
int main(){
	freopen("/home/slyfc/vimFile/in","r",stdin);
	scanf("%d%d",&n,&m);
	if(m==0){
		printf("1\n1\n");
		return 0;
	}
	for(int i=0;i<m;i++){
		scanf("%d%d",&es[i][0],&es[i][1]);
		deg[es[i][0]]++,deg[es[i][1]]++;
	}
	s=0,t=n+1;
	U=m;
	double l=0,r=m;
	while(r-l>1.0/n/n){
		double mid=(r+l)/2;
		build(mid);
		double res=maxFlow();
		double tmp=U*n-res;
		if(tmp>eps) l=mid;
		else r=mid;
	}
	dfs(0);
	int cnt=0;
	for(int i=1;i<=n;i++) if(vis[i]) cnt++;
	cout<<cnt<<endl;
	for(int i=1;i<=n;i++) if(vis[i]){
		printf("%d\n",i);
	}
	return 0;
}

