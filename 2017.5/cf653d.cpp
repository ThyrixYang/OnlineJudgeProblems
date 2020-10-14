#include <bits/stdc++.h>

using namespace std;

#define INF (0x3f3f3f3f)
const int MAXV=100;
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
const double eps=1e-13;
const int maxn=600;
int n,m,x;
int a[maxn],b[maxn],c[maxn];
int cal(double f){
	int s=1,t=n;
	dinic_init();
	for(int i=0;i<m;i++){
		int cap=c[i]/f+eps;
		cap=min(cap,x);
		addedge(a[i],b[i],cap);
	}
	int res=dinic(s,t);
	return res;
}
int main(){
	freopen("./in","r",stdin);
	cin>>n>>m>>x;
	for(int i=0;i<m;i++)
		scanf("%d%d%d",&a[i],&b[i],&c[i]);
	double l=1.0/x,r=1e6;
	while(r-l>1e-8){
		double mid=(r+l)/2;
		int res=cal(mid);
		if(res>=x) l=mid;
		else r=mid;
	}
	printf("%.15f\n",l*x);
	return 0;
}
