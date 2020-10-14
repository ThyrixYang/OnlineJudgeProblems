#include<bits/stdc++.h>
using namespace std;
const int MAXV=20000;
const int MAXE=1000000;
#define INF (0x3f3f3f3f)
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

const int maxn=105;
struct Node{
	int a,b;
	Node(){}
	Node(char *s){
		if(s[0]=='.') a=-1,b=-1;
		else{
			s[3]=0;
			if(s[0]=='X') a=-2;
			else a=atoi(s);
			if(s[4]=='X') b=-2;
			else b=atoi(s+4);
		}
	}
}a[maxn][maxn];
int n,m;
char s[maxn];
int anse[MAXV];
int idc[MAXV],idr[MAXV];
void solve(){
	dinic_init();
	int s=MAXV-1,t=MAXV-2;
	int sum=0;
	int ic=0,ir=10000;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(a[i][j].a>0){
				for(int k=i+1;k<n;k++){
					if(a[k][j].a!=-1) break;
					idc[k*m+j]=ic;
					a[i][j].a--;
				}
				sum+=a[i][j].a;
				addedge(s,ic,a[i][j].a);
				ic++;
			}
			if(a[i][j].b>0){
				for(int k=j+1;k<m;k++){
					if(a[i][k].a!=-1) break;
					idr[i*m+k]=ir;
					a[i][j].b--;
				}
				addedge(ir,t,a[i][j].b);
				ir++;
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(a[i][j].a==-1){
				addedge(idc[i*m+j],idr[i*m+j],8);
				anse[i*m+j]=eh-1;
			}
		}
	}
	int res=dinic(s,t);
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(a[i][j].a==-1){
				printf("%d",ES[anse[i*m+j]].cap+1);
			}else printf("_");
			if(j<m-1) printf(" ");
		}
		puts("");
	}
}
int main(){
	freopen("/home/slyfc/vimFile/in","r",stdin);
	while(cin>>n>>m){
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				scanf("%s",s);
				a[i][j]=Node(s);
			}
		}
		solve();
	}
	return 0;
}
