#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> P;
#define fs first
#define se second
#define pb push_back
const int maxn=600;
const int maxv=maxn*maxn;
const int INF=(0x3f3f3f3f);
const int maxe=maxv*5;
struct EDGE{
	int to,w,t,next;
	EDGE(int to=0,int w=0,int t=0):to(to),w(w),t(t){}
}E[maxe];
int head[maxv],eh=0;
void addedge(int from,int to,int w,int t){
	E[eh]=EDGE(to,w,t);
	E[eh].next=head[from];
	head[from]=eh++;
}
char B[maxn][maxn];
int T;
int n,m;
int sc,sr,tc,tr;
P dis[maxv];
void init(){
	eh=0;
	for(int i=0;i<n*m;i++) dis[i]=P(INF,INF);
	memset(head,-1,sizeof head);
}
const int drx[]={-1,1,0,0};
const int dry[]={0,0,-1,1};
const int drx8[]={-1,1,0,0,1,-1,1,-1};
const int dry8[]={0,0,1,-1,1,1,-1,-1};
bool out(int x,int y){
	return x<0||y<0||x>=n||y>=m;
}
int calNear(int x,int y){	
	int ans=0;
	for(int i=0;i<4;i++){
		int dx=x+drx[i],dy=y+dry[i];
		if(out(dx,dy)||B[dx][dy]=='#') continue;
		if(isupper(B[dx][dy])) ans+=B[dx][dy]-'A'+1;
	}
	if(islower(B[x][y])) ans+=B[x][y]-'a'+1;
	return ans;
}
int id(int x,int y){
	return x*m+y;
}
P operator + (const P &A,const P &B){
	return P(A.fs+B.fs,A.se+B.se);
}
void build(){
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(B[i][j]=='#') continue;
			for(int k=0;k<4;k++){
				int dx=i+drx[k],dy=j+dry[k];
				if(out(dx,dy)||B[dx][dy]=='#') continue;
				int cost=calNear(dx,dy);
				if(isupper(B[i][j])) cost-=B[i][j]-'A'+1;
				addedge(id(i,j),id(dx,dy),cost,1);
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(!isupper(B[i][j])) continue;
			for(int k1=0;k1<4;k1++){
				int x1=i+drx[k1],y1=j+dry[k1];
				if(out(x1,y1)) continue;
				for(int k2=0;k2<4;k2++){
					int x2=i+drx[k2],y2=j+dry[k2];
					if(out(x2,y2)||(x1==x2&&y1==y2)) continue;
					int v=id(x1,y1);
					int u=id(x2,y2);
					int cnt=0;
					for(int k3=0;k3<8;k3++){
						int x3=i+drx8[k3],y3=j+dry8[k3];
						if(!out(x3,y3)&&isupper(B[x3][y3])){
							if(abs(x3-x1)+abs(y3-y1)==1
								&&	abs(x2-x3)+abs(y3-y2)==1)
								cnt+=B[x3][y3]-'A'+1;
						}
					}
					cnt+=B[i][j]-'A'+1;
					addedge(id(x1,y1),id(x2,y2),calNear(x2,y2)-cnt,2);
				}
			}
		}
	}
}
#define mp make_pair
void dij(){
	priority_queue<pair<P,int> > Q;
	dis[id(sr,sc)]=P(0,0);
	Q.push(mp(dis[id(sr,sc)],id(sr,sc)));
	while(!Q.empty()){
		P d=Q.top().fs;
		int v=Q.top().se;
		d.fs=-d.fs;
		d.se=-d.se;
		Q.pop();
		if(dis[v]<d) continue;
		for(int i=head[v];i!=-1;i=E[i].next){
			EDGE &e=E[i];
			int to=e.to,w=e.w,t=e.t;
			if(dis[v]+P(w,t)<dis[to]){
				dis[to]=dis[v]+P(w,t);
				Q.push(mp(P(-dis[to].fs,-dis[to].se),to));
			}
		}
	}
}
int main(){
	freopen("./in","r",stdin);
	cin>>T;
	while(T--){
		scanf("%d%d",&n,&m);
		init();
		scanf("%d%d%d%d",&sr,&sc,&tr,&tc);
		sr--,sc--,tr--,tc--;
		for(int i=0;i<n;i++) scanf("%s",B[i]);
		build();
		dij();
		int t=id(tr,tc);
		printf("%d %d\n",dis[t].fs,dis[t].se);
	}
	return 0;
}
