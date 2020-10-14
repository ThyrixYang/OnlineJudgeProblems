#include <bits/stdc++.h>
using namespace std;
const int MAXV=3000;
const int MAXE=1000000;
const int INF = 1e9 + 7;
struct EDGE{
    int to,cap,next;
}ES[MAXE];
int head[MAXV];
int eh;
void addEdge(int from,int to,int cap){///加边
    ES[eh].to=to,ES[eh].cap=cap,ES[eh].next=head[from];
    head[from]=eh++;
    ES[eh].to=from,ES[eh].cap=0,ES[eh].next=head[to];
    head[to]=eh++;
}
void addEdge2(int from,int to,int cap){///加边
    ES[eh].to=to,ES[eh].cap=cap,ES[eh].next=head[from];
    head[from]=eh++;
    ES[eh].to=from,ES[eh].cap=cap,ES[eh].next=head[to];
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

int T, n, m;
int cas = 0;
char B[50][50];
void link(int x1, int y1, int x2, int y2) {
	int v = x1 * m + y1, u = x2 * m + y2;
	if(B[x1][y1] == '.') {
		if(B[x2][y2] == '.') {
			addEdge2(v, u, INF);
		} else if(B[x2][y2] == 'E') {
			addEdge2(v, u, 
		} else {

		}
	} else if(B[x1][y1] == 'E') {
		if(B[x2][y2] == '.') {

		} else if(B[x2][y2] == 'E') {

		} else {

		}
	} else {
		if(B[x2][y2] == '.') {

		} else if(B[x2][y2] == 'E') {

		} else {

		}
	}
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		printf("Case %d: ", ++cas);
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; i++)
			scanf("%s", B[i]);
		dinic_init();
		int cnt = 0;
		int s = n * m + 1, t = s + 1;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if(B[i][j] == '.') {
					addEdge(s, i * m + j, INF);
				} else if(B[i][j] == 'E') {
					
				} else {
					addEdge(i * m + j, t, INF);
				}
			}
		}
	}
	return 0;
}
