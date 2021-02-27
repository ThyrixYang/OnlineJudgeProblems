#include <bits/stdc++.h>

using namespace std;
#define se second
#define fs first

typedef pair<int,int> P;
const int maxn=205;
int dis1[maxn][maxn];
int dis2[maxn][maxn];
char B[maxn][maxn];
const int drx[]={0,0,-1,1};
const int dry[]={-1,1,0,0};
int n,m;
void bfs(int sx,int sy,int dis[][maxn]){
	memset(dis,0x3f,sizeof(int)*(maxn*maxn));
	dis[sx][sy]=0;
	queue<P> Q;
	Q.push(P(sx,sy));
	while(!Q.empty()){
		int x=Q.front().fs,y=Q.front().se;
		Q.pop();
		for(int i=0;i<4;i++){
			int dx=x+drx[i],dy=y+dry[i];
			if(dx<0||dx>=n||dy<0||dy>=m||B[dx][dy]=='B') continue;
			if(dis[dx][dy]>dis[x][y]+1){
				dis[dx][dy]=dis[x][y]+1;
				Q.push(P(dx,dy));
			}
		}
	}
}
int xb,yb;
int xr,yr;
vector<P> av1,av2;
int main(){
	//freopen("/home/cwind/vimFile/in","r",stdin);
	freopen("labyrinth.in","r",stdin);
	freopen("labyrinth.out","w",stdout);
	cin>>n>>m;
	for(int i=0;i<n;i++)
		scanf("%s",B[i]);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			if(B[i][j]=='R') xr=i,yr=j;
			if(B[i][j]=='S') xb=i,yb=j;
		}
	bfs(xr,yr,dis1);
	bfs(xb,yb,dis2);
	int mdis=dis1[xb][yb];
	if(mdis>1e9){
		puts("2");
		return 0;
	}
	if(mdis%2==0){
		int cnt=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(dis1[i][j]==dis2[i][j]&&dis1[i][j]==mdis/2) cnt++;
			}
		}
		if(cnt>1){
			puts("2");
		}else{
			puts("1");
		}
		return 0;
	}else{
		int d=mdis/2;
		int cnt=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(dis1[i][j]==d){
					for(int k=0;k<4;k++){
						int x=i+drx[k],y=j+dry[k];
						if(x<0||x>=n||y<0||y>=m) continue;
						if(dis2[x][y]==d) cnt++;
					}
				}
			}
		}
		if(cnt>1){
			puts("2");
		}else{
			puts("1");
		}
	}
	return 0;
}
