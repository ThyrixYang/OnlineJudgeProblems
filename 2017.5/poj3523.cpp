#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

struct hashTable{
	static const int mod=1234577;
	static const int tol=2e6;
	int head[mod],key[tol],next[tol],dat[tol];
	int sz;
	void init(){
		memset(head,-1,sizeof head);
		sz=0;
	}
	int find(int x){
		int id=x%mod;
		int p=-1;
		for(int i=head[id];i!=-1;i=next[i]){
			if(key[i]==x){
				p=i;
				break;
			}
		}
		return p;
	}
	void insert(int x,int v){
		int id=x%mod;
		key[sz]=x;
		next[sz]=head[id];
		dat[sz]=v;
		head[id]=sz++;
	}
}T;
char B[14][14];
int w,h,n;
char s[200];
int dis[500][500];
int des[3];
int st[3];
struct Node{
	int a[3];
	int d,h1,h2;
	Node(int w=0,int x=0,int y=0,int z=0){
		a[0]=x,a[1]=y,a[2]=z,d=w;
		h1=0,h2=0;
		for(int i=0;i<n;i++)
			h1=max(h1,dis[a[i]][des[i]]),h2+=dis[a[i]][des[i]];
		h1+=d;
	}
	bool operator < (const Node &C)const{
		if(h1!=C.h1) return h1>C.h1;
		return h2>C.h2;
	}
};
const int drx[]={0,0,-1,1,0};
const int dry[]={-1,1,0,0,0};
void shortest_path(){
	memset(dis,0x3f,sizeof dis);
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			int v=i*w+j;
			if(B[i][j]=='#') continue;
			for(int k=0;k<5;k++){
				int dx=i+drx[k],dy=j+dry[k];
				if(dx<0||dx>=h||dy<0||dy>=w) continue;
				if(B[dx][dy]=='#') continue;
				int u=dx*w+dy;
				dis[u][v]=dis[v][u]=1;
			}
		}
	}
	for(int i=0;i<w*h;i++) dis[i][i]=0;
	for(int k=0;k<w*h;k++)
		for(int i=0;i<w*h;i++)
			for(int j=0;j<w*h;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
}
void getPos(){
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			int v=i*w+j;
			if(B[i][j]=='a') st[0]=v;
			if(B[i][j]=='A') des[0]=v;
			if(B[i][j]=='b') st[1]=v;
			if(B[i][j]=='B') des[1]=v;
			if(B[i][j]=='c') st[2]=v;
			if(B[i][j]=='C') des[2]=v;
			if(B[i][j]!='#') B[i][j]='.';
		}
	}
}
char out[14][14];
int p[3],mv[3][100];
int mh[3];
int code(int a,int b,int c){
	return a+b*200+c*40000;
}
int mm[3];
int main(){
	freopen("/home/slyfc/vimFile/in","r",stdin);
	while(scanf("%d%d%d",&w,&h,&n)){
		gets(s);
		if(w==0&&h==0&&n==0) break;
		gets(s);
		for(int i=0;i<h-2;i++){
			gets(s);
			for(int j=0;j<w-2;j++)
				B[i][j]=s[j+1];
		}
		gets(s);
		w-=2,h-=2;
		shortest_path();
		getPos();
		T.init();
		priority_queue<Node> Q;
		Q.push(Node(0,st[0],st[1],st[2]));
		T.insert(code(st[0],st[1],st[2]),0);
		int ans=1e9;
		int cnt=0;
		while(!Q.empty()){
			for(int i=0;i<n;i++)
				p[i]=Q.top().a[i];
			bool f=1;
			for(int i=0;i<n;i++) if(p[i]!=des[i]) f=0;
			int d=Q.top().d;
			if(f){
				ans=min(ans,d);
				break;
				cnt++;
				if(cnt>100) break;
			}
			Q.pop();
			memset(mh,0,sizeof mh);
			for(int i=0;i<n;i++){
				int x=p[i]/w,y=p[i]%w;
				for(int k=0;k<5;k++){
					int dx=x+drx[k],dy=y+dry[k];
					if(dx<0||dx>=h||dy<0||dy>=w||B[dx][dy]=='#') continue;
					mv[i][mh[i]++]=dx*w+dy;
				}
			}
			if(n<2) mh[1]=1,mv[1][0]=0;
			if(n<3) mh[2]=1,mv[2][0]=0;
			for(int i=0;i<mh[0];i++){
				for(int j=0;j<mh[1];j++){
					for(int k=0;k<mh[2];k++){
						mm[0]=mv[0][i];
						mm[1]=mv[1][j];
						mm[2]=mv[2][k];
						bool f=1;
						for(int x=0;x<n&&f;x++){
							for(int y=x+1;y<n&&f;y++){
								if(p[x]==mm[y]&&p[y]==mm[x]||mm[x]==mm[y]){
									f=0;
									break;
								}
							}
						}
						if(!f) continue;
						int idx=code(mm[0],mm[1],mm[2]);
						int pp=T.find(idx);
						if(pp==-1) T.insert(idx,d+1),Q.push(Node(d+1,mm[0],mm[1],mm[2]));
						else{
							if(T.dat[pp]>d+1){
								T.dat[pp]=d+1;
								Q.push(Node(d+1,mm[0],mm[1],mm[2]));
							}
						}
					}
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
