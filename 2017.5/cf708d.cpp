#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<long long, int> P;
#define se second
#define fs first
#define INF 1e9
const int MAXV=500;
const int MAXE=1e6;
const int MAXN = 200;
struct EDGE{
	int to,cap,cost,next;
}ES[MAXE];
int eh;
int h[MAXV];
int dis[MAXV];
int prevv[MAXV],preve[MAXV];
int head[MAXV];
void addEdge(int from,int to,int cap,int cost){
	ES[eh].to=to;ES[eh].cap=cap;ES[eh].cost=cost;
	ES[eh].next=head[from];head[from]=eh++;
	ES[eh].to=from;ES[eh].cap=0;ES[eh].cost=-cost;
	ES[eh].next=head[to];head[to]=eh++;
}
bool inq[MAXV];
ll min_cost_flow(int s,int t,int f){
	int V=MAXV;//default V size maxed
	ll res=0;
	memset(h,0,sizeof h);
	queue<P> Q;////spfa计算势h,有时候裸的spfa可能比较快....
	fill(dis,dis+V,INF);
	dis[s]=0;
	Q.push(P(0,s));
	inq[s]=1;
	while(!Q.empty()){
		P p=Q.front();Q.pop();
		int v=p.se;
		inq[v]=0;
		for(int i=head[v];i!=-1;i=ES[i].next){
			EDGE &e=ES[i];
			if(e.cap>0&&dis[e.to]>dis[v]+e.cost+h[v]-h[e.to]){
				dis[e.to]=dis[v]+e.cost +h[v]-h[e.to];
				prevv[e.to]=v;
				preve[e.to]=i;
				if(!inq[e.to]) Q.push(P(dis[e.to],e.to)),inq[e.to]=1;
			}
		}
	}
	for(int v=0;v<V;v++)
		h[v]+=dis[v];
	while(f>0){
		priority_queue<P,vector<P> ,greater<P> >Q;////Dijkstra计算势h,也可裸跑spfa
		fill(dis,dis+V,INF);
		dis[s]=0;
		Q.push(P(0,s));
		while(!Q.empty()){
			P p=Q.top();Q.pop();
			int v=p.se;
			if(dis[v]<p.fs) continue;
			for(int i=head[v];i!=-1;i=ES[i].next){
				EDGE &e=ES[i];
				if(e.cap>0&&dis[e.to]>dis[v]+e.cost+h[v]-h[e.to]){
					dis[e.to]=dis[v]+e.cost +h[v]-h[e.to];
					prevv[e.to]=v;
					preve[e.to]=i;
					Q.push(P(dis[e.to],e.to));
				}
			}
		}
		if(dis[t]==INF) return res;
		for(int v=0;v<V;v++) h[v]+=dis[v];
		int d=f;
		for(int v=t;v!=s;v=prevv[v])
			d=min(d,ES[preve[v]].cap);
		f-=d;
		res+=d*h[t];
		for(int v=t;v!=s;v=prevv[v]){
			EDGE &e=ES[preve[v]];
			e.cap-=d;
			ES[preve[v]^1].cap+=d;
		}
	}
	return res;
}
void clear_G(){
	eh=0;
	memset(head,-1,sizeof head);
}
int N, M;
int F[MAXN];
int main() {
	freopen("./in", "r", stdin);
	scanf("%d%d", &N, &M);
	clear_G();
	int S = N + 1, T = N + 2;
	int cost = 0;
	while(M--) {
		int u, v, c, f;
		scanf("%d%d%d%d", &u, &v, &c, &f);
		F[v] += f;
		F[u] -= f;
		if(c >= f) {
			addEdge(u, v, c - f, 1);
			addEdge(v, u, f, 1);
			addEdge(u, v, 1e9, 2);
		} else {
			cost += f - c;
			addEdge(v, u, f - c, 0);
			addEdge(v, u, c, 1);
			addEdge(u, v, 1e9, 2);
		}
	}
	for(int i = 1; i <= N; i++) {
		if(F[i] > 0) {
			addEdge(S, i, F[i], 0);
		} else if(F[i] < 0) {
			addEdge(i, T, -F[i], 0);
		}
	}
	addEdge(N, 1, 1e9, 0);
	cost += min_cost_flow(S, T, 1e9);
	printf("%d", cost);
	return 0;
}
