#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> P;
#define y1 wer
const int maxn=1005;
char B[maxn][maxn];
int d[maxn][maxn][4];
int dis[maxn][maxn][4];
int n,m;
int x1,y1,x2,y2;
int drx[]={-1,0,1,0};//U,R,D,L
int dry[]={0,1,0,-1};
int tran[4]={2,3,0,1};
int id(int x,int y,int dr){
	return x*m*4+y*4+dr;
}
int main(){
	freopen("./in","r",stdin);
	cin>>n>>m;
	for(int i=0;i<n;i++){
		scanf("%s",B[i]);
		for(int j=0;j<m;j++){
			int* a=d[i][j];
			char c=B[i][j];
			if(c=='+') a[0]=a[1]=a[2]=a[3]=1;
			else if(c=='-') a[1]=a[3]=1;
			else if(c=='|') a[0]=a[2]=1;
			else if(c=='^') a[0]=1;
			else if(c=='>') a[1]=1;
			else if(c=='<') a[3]=1;
			else if(c=='v') a[2]=1;
			else if(c=='L') a[0]=a[1]=a[2]=1;
			else if(c=='R') a[0]=a[2]=a[3]=1;
			else if(c=='U') a[1]=a[2]=a[3]=1;
			else if(c=='D') a[0]=a[1]=a[3]=1;
		}
	}
	cin>>x1>>y1>>x2>>y2;
	x1--,y1--,x2--,y2--;
	memset(dis,0x3f,sizeof dis);
	dis[x1][y1][0]=0;
	priority_queue<P,vector<P>,greater<P> > Q;
	Q.push(P(0,id(x1,y1,0)));
	while(!Q.empty()){
		int s=Q.top().second;
		int td=Q.top().first;
		Q.pop();
		int x=s/(m*4),y=s/4%m,dr=s%4;
		if(dis[x][y][dr]<td) continue;
		for(int k=0;k<4;k++){
			int dx=x+drx[k],dy=y+dry[k];
			if(dx<0||dx>=n||dy<0||dy>=m) continue;
			if(!d[x][y][(k+dr*3)%4]) continue;
			if(!d[dx][dy][(tran[k]+dr*3)%4]) continue;
			if(dis[dx][dy][dr]>dis[x][y][dr]+1){
				dis[dx][dy][dr]=dis[x][y][dr]+1;
				Q.push(P(dis[dx][dy][dr],id(dx,dy,dr)));
			}
		}
		if(dis[x][y][(dr+1)%4]>dis[x][y][dr]+1){
			dis[x][y][(dr+1)%4]=dis[x][y][dr]+1;
			Q.push(P(dis[x][y][(dr+1)%4],id(x,y,(dr+1)%4)));
		}
	}
	int ans=1e9+7;
	for(int i=0;i<4;i++) ans=min(ans,dis[x2][y2][i]);
	if(ans>1e8) puts("-1");
	else cout<<ans<<endl;
	return 0;
}
