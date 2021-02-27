#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
#define se second
#define fs first
const int MAXV=500;
const int MAXE=1e6;
const int INF = 1e9;
struct EDGE{
	int to,cap,cost,next;
}ES[MAXE];
int eh;
int h[MAXV];
int dis[MAXV];
int prevv[MAXV],preve[MAXV];
int head[MAXV];
void addedge(int from,int to,int cap,int cost){
	ES[eh].to=to;ES[eh].cap=cap;ES[eh].cost=cost;
	ES[eh].next=head[from];head[from]=eh++;
	ES[eh].to=from;ES[eh].cap=0;ES[eh].cost=-cost;
	ES[eh].next=head[to];head[to]=eh++;
}
bool inq[MAXV];
ll min_cost_flow(int s,int t,int f){
	int V=MAXV;
	ll res=0;
	memset(h,0,sizeof h);
	while(f>0){
		priority_queue<P,vector<P> ,greater<P> >Q;
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
		if(dis[t]==INF) return -1;
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

int Ts, n, m, k;
int p[1000];
int pp, Q;
int S[205], T[205];
int main() {
	freopen("./in", "r", stdin);
	std::cin >> Ts;
	while(Ts--) {
		clear_G();
		int sum = 0;
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; i++) scanf("%d", &p[i]), sum += p[i];
		scanf("%d%d%d", &m, &pp, &Q);
		for(int i = 0; i < m; i++) {
			scanf("%d%d", &S[i], &T[i]);
		}
		int s = n * 2 + 1, t = s + 1;
		addedge(s, 1, k, 0);
		for(int i = 1; i <= n; i++) {
			if(i < n) addedge(i, i + 1, INF, 0);
			addedge(i, t, p[i], 0);
			addedge(s, i + n, p[i], 0);
			for(int j = 0; j < m; j++) {
				int c = S[j], ne = i + T[j];
				if(ne > n) continue;
				addedge(i + n, ne, INF, S[j]);
			}
		}
		addedge(s, pp, INF, Q);
		int ans = min_cost_flow(s, t, sum);
		if(ans == -1) {
			puts("No solution");
		}else{
			printf("%d\n", ans);
		}
	}
	return 0;
}
