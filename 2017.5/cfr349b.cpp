#include <bits/stdc++.h>

using namespace std;

const int maxn=4000;
int n,m;
vector<int> G[maxn];
int dis[maxn][maxn];
int maxto[maxn][4];
int maxfrom[maxn][4];
void update(int d[][4],int v,int u,int len){
	if(d[v][1]<len) d[v][1]=len,d[v][3]=u;
	if(d[v][1]>d[v][0]) swap(d[v][1],d[v][0]),swap(d[v][2],d[v][3]);
}
void bfs(int s){
	dis[s][s]=0;
	queue<int> Q;
	Q.push(s);
	while(!Q.empty()){
		int v=Q.front();
		Q.pop();
		for(int i=0;i<G[v].size();i++){
			int u=G[v][i];
			if(dis[s][u]==-1){
				dis[s][u]=dis[s][v]+1,Q.push(u);
				update(maxto,s,u,dis[s][u]);
				update(maxfrom,u,s,dis[s][u]);
			}
		}
	}
}
int ans[4];
int maxdis=0;
int main(){
	freopen("./in","r",stdin);
	memset(dis,-1,sizeof dis);
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		G[x].push_back(y);
	}
	for(int i=1;i<=n;i++) bfs(i);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j||dis[i][j]==-1) continue;
			for(int p1=2;p1<4;p1++){
				for(int p2=2;p2<4;p2++){
					int vf=maxfrom[i][p1];
					int vt=maxto[j][p2];
					int df=maxfrom[i][p1-2];
					int dt=maxto[j][p2-2];
					if(vf==i||vf==vt||vf==j||vt==i||vt==j||vf==0||vt==0) continue;
					int d=dis[i][j]+df+dt;
					if(d>maxdis){
						maxdis=d;
						ans[0]=vf;
						ans[1]=i;
						ans[2]=j;
						ans[3]=vt;
					}
				}
			}
		}
	}
	for(int i=0;i<4;i++) cout<<ans[i]<<" ";
	return 0;
}
