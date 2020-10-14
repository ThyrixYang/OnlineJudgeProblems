#include <bits/stdc++.h>

using namespace std;
const int MAXV = 12000;
const int MAXE = 1000000;
const int INF = 1e7;
int cas = 0;
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

int T;
int n;
char s[1000];
int x[10000];
int a[200], b[200];
int w[200][200];
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		dinic_init();
		scanf("%d", &n);
		scanf("%s", s);
		for(int i = 0; i < n; i++) x[i] = s[i] - '0';
		int s = n * n + n + 10 + 1;
		int t = s + 1;
		int sum = 0;
		for(int i = 0; i < 10; i++) {
			scanf("%d%d", &a[i], &b[i]);
			if(b[i] - a[i] > 0) addedge(n * n + n + i, t, b[i] - a[i]);
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				scanf("%d", &w[i][j]);
			}
		}
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				sum += w[j][i] + w[i][j];
				addedge(s, i * n + j, w[i][j] + w[j][i]);
				addedge(i * n + j, n * n + j, INF);
				addedge(i * n + j, n * n + i, INF);
			}
		}
		for(int i = 0; i < n; i++) {
			addedge(n * n + i, t, a[x[i]]);
			addedge(n * n + i, n * n + n + x[i], INF);
		}
		int res = dinic(s, t);
		printf("Case #%d: %d\n", ++cas, sum - res);
	}
	return 0;
}
