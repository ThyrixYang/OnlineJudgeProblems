#include <bits/stdc++.h>

using namespace std;

#define INF (0x3f3f3f3f)
typedef long long ll;
typedef pair<int,int> P;
#define fs first
#define se second
const int MAXV=5005;
const int MAXE=1e6;
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
int V;
int Q[MAXE],front,back;
int min_cost_flow(int s,int t,int f){
	int res=0;
	while(f>0){
		front=back=0;
		fill(dis,dis+V,INF);
		dis[s]=0;
		Q[back++]=s;
		while(front<back){
			int v=Q[front++];
			inq[v]=0;
			for(int i=head[v];i!=-1;i=ES[i].next){
				EDGE &e=ES[i];
				if(e.cap>0&&dis[e.to]>dis[v]+e.cost){
					dis[e.to]=dis[v]+e.cost;
					prevv[e.to]=v;
					preve[e.to]=i;
					if(!inq[e.to]) Q[back++]=e.to,inq[e.to]=1;
				}
			}
		}
		if(dis[t]==INF) return -1;
		int d=f;
		for(int v=t;v!=s;v=prevv[v])
			d=min(d,ES[preve[v]].cap);
		f-=d;
		res+=d*dis[t];
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
int Ts;
int n,m;
int B[60][60];
int R,S;
void AddEdge(int x1,int y1,int x2,int y2,int c){
	if(B[x2][y2]!=0&&B[x2][y2]%2==0) return;
	if(B[x1][y1]%2==1) return;
	if(B[x1][y1]==0){
		addedge(x1*m+y1+n*m,x2*m+y2,1,c);
	}else{
		if(B[x2][y2]==0||B[x2][y2]%2==1) addedge(x1*m+y1,x2*m+y2,1,c);
	}
}
int cas=0;
int main(){
	freopen("./in","r",stdin);
	scanf("%d",&Ts);
	while(Ts--){
		printf("Case #%d: ",++cas);
		clear_G();
		int cnt[2];
		cnt[0]=cnt[1]=0;
		scanf("%d%d",&n,&m);
		R=n*m*2+1,S=n*m*2+2;
		V=S+1;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				scanf("%d",&B[i][j]);
				if(B[i][j]!=0) cnt[B[i][j]%2]++;
			}
		for(int i=0;i<n-1;i++){
			for(int j=0;j<m;j++){
				int x;
				scanf("%d",&x);
				AddEdge(i,j,i+1,j,x);
				AddEdge(i+1,j,i,j,x);
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m-1;j++){
				int x;
				scanf("%d",&x);
				AddEdge(i,j,i,j+1,x);
				AddEdge(i,j+1,i,j,x);
			}
		}
		if(cnt[0]!=cnt[1]){
			puts("-1");
			continue;
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(B[i][j]==0){
					addedge(R,i*m+j+n*m,1,0);
					addedge(i*m+j,S,1,0);
				}else if(B[i][j]%2==0){
					addedge(R,i*m+j,1,0);
				}else{
					addedge(i*m+j,S,1,0);
				}
			}
		}
		printf("%d\n",min_cost_flow(R,S,n*m-cnt[0]));
	}
	return 0;
}
