#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
#define prev sdsfsdf
const int maxe=1e6;
const int maxv=205;
struct EDGE{
	int to,cap,cost,next;
	EDGE(int to=0,int cap=0,int cost=0,int next=0):to(to),cap(cap),cost(cost),next(next){}
}E[maxe];
int head[maxv],eh;
void addedge(int from,int to,int cap,int cost){
	E[eh]=EDGE(to,cap,cost,head[from]);
	head[from]=eh++;
	E[eh]=EDGE(from,0,-cost,head[to]);
	head[to]=eh++;
}
int dis[maxv];
int Q[maxe],front,back;
int in[maxv];
int prev[maxv],pree[maxv];
void spfa(int s){
	memset(dis,0x3f,sizeof dis);
	memset(in,0,sizeof in);
	dis[s]=0;
	front=back=0;
	Q[back++]=s;
	while(front<back){
		int v=Q[front++];
		in[v]=0;
		for(int i=head[v];i!=-1;i=E[i].next){
			EDGE &e=E[i];
			if(e.cap==0) continue;
			if(dis[e.to]>dis[v]+e.cost){
				dis[e.to]=dis[v]+e.cost;
				if(!in[e.to]) Q[back++]=e.to,in[e.to]=1;
				prev[e.to]=v,pree[e.to]=i;
			}
		}
	}
}
void min_cost_flow(int &flow,int &cost,int s,int t){
	flow=0,cost=0;
	spfa(s);
	while(dis[t]<1e9){
		flow++;
		cost+=dis[t];
		for(int i=t;i!=s;i=prev[i]){
			int j=pree[i];
			E[j].cap--,E[j^1].cap++;
		}
		spfa(s);
	}
}
void init(){
	memset(head,-1,sizeof head);
	eh=0;
}
int n,m;
int nextv[maxv];
int ind[maxv];
int out[maxv],oh;
void build(){
	for(int i=1;i<=n;i++) nextv[i]=i;
	for(int i=1;i<=n;i++){
		for(int j=head[i];j!=-1;j=E[j].next){
			EDGE &e=E[j];
			if(e.to>n&&e.cap==0){
				ind[e.to-n]++;
				nextv[i]=e.to-n;
			}
		}
	}
}
int main(){
	freopen("/home/slyfc/vimFile/in","r",stdin);
	init();
	cin>>n>>m;
	int s=0,t=n*2+1;
	for(int i=0;i<m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		addedge(x,y+n,1,z);
	}
	for(int i=1;i<=n;i++){
		addedge(s,i,1,0);
		addedge(i+n,t,1,0);
	}
	int flow,cost;
	min_cost_flow(flow,cost,s,t);
	cout<<n-flow<<" "<<cost<<endl;
	build();
	for(int i=1;i<=n;i++){
		if(ind[i]==0){
			oh=0;
			int j=i;
			for(;;){
				out[oh++]=j;
				if(nextv[j]==j) break;
				j=nextv[j];
			}
			printf("%d",oh);
			for(int j=0;j<oh;j++){
				printf(" %d",out[j]);
			}
			puts("");
		}
	}
	return 0;
}
