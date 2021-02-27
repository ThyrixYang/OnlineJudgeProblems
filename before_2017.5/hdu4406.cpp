#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <utility>

using namespace std;


int maxv=1e3;
int maxe=1e6;
struct EDGE{
	int to,next;
	double cap;
	EDGE(int to,double cap,int next):to(to),cap(cap),next(next){}
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
int dis[maxv];
int Q[maxe],front,back;
void bfs(int s){
	memset(dis,0x3f,sizeof dis);
	dis[s]=0;
	front=back=0;
	Q[back++]=s;
	while(front<back){
		int v=Q[front++];
		for(int i=head[v];i!=-1;i=E[i].next){
			EDGE &e=E[i];
			if(e.cap>0&&dis[e.to]>dis[v]+1){
				dis[e.to]=dis[v]+1;
				Q[back++]=e.to;
			}
		}
	}
}
int iter[maxv];
double dfs(int v,int f){
	for(int i=iter[v];i!=-1;i=E[i].next){
		EDGE &e=E[i];
		double d=dfs(e.to,min(e.cap,f));
		if(d){
			e.cap-=d,E[i^1].cap+=d;
			return d;
		}
	}
	return 0;
}
double maxFlow(int s,int t){
	double flow=0;
	for(;;){
		bfs(s);
		if(dis[t]>1e9) return flow;
		double d;
		for(int i=0;i<maxv;i++) iter[i]=head[i];
		while(d=dfs(s,INF)) flow+=d;
	}
}
int main(){
	freopen("/home/slyfc/vimFile/in","r",stdin);
	
	return 0;
}
