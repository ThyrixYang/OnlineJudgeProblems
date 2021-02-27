#include <bits/stdc++.h>

const int MAXV = 1000;
const int MAXE = 1000000;
const int INF = 1e9;
struct EDGE{
    int to, cap, next;
}ES[MAXE];
int head[MAXV];
int eh;
void addEdge(int from,int to,int cap){
    ES[eh].to = to, ES[eh].cap = cap, ES[eh].next = head[from];
    head[from] = eh++;
    ES[eh].to = from, ES[eh].cap = 0, ES[eh].next = head[to];
    head[to] = eh++;
}
int level[MAXV];
int vis[MAXV];
int tm;
int Q[MAXE], front, back;
int bfs(int s, int t){
	tm++;
    level[s] = 0;
	front = back = 0;
	Q[back++] = s;
    while(front < back){
        int v = Q[front++];
		vis[v] = tm;
        for(int i = head[v]; i != -1;i = ES[i].next){
            EDGE &e = ES[i];
            if(e.cap > 0 && vis[e.to] != tm){
                level[e.to] = level[v] + 1;
                Q[back++] = e.to;
            }
        }
    }
	return vis[t] == tm;
}
int iter[MAXV];
int dfs(int v,int t,int f){
    if(v==t) return f;
	int res = 0;
    for(int &i=iter[v]; i != -1;i = ES[i].next){
        EDGE &e = ES[i];
        if(e.cap > 0 && vis[e.to] == tm && level[e.to] > level[v]){
            int d=dfs(e.to,t,std::min(f - res,e.cap));
            if(d>0){
				res += d;
                e.cap-=d;
                ES[i^1].cap+=d;
            }
			if(res == f) return f;
        }
    }
	return res;
}
int n, m, k;
int dinic(int s,int t){
    int flow=0;
    for(;;){
        if(!bfs(s, t)) return flow;
        for(int i=0; i < n + m + 2;i++) iter[i]=head[i];
        int f;
        while((f=dfs(s,t,INF))>0) flow+=f;
    }
    return 0;
}
void dinic_init(){
	std::memset(head,-1,sizeof(int) * (n + m + 3));
    eh=0;
}

int id[500][500];
int vis2[MAXV];
int dfs1(int v, int f = -1) {
	vis[v] = tm;
	vis2[v] = 1;
	for(int i = head[v]; i != -1; i = ES[i].next) {
		int u = ES[i].to;
		if(u == f || !ES[i].cap || (vis2[u] && vis[u] != tm)) continue;
		if(vis[u] == tm) return 0;
		if(!dfs1(u, v)) return 0;
	}
	return 1;
}
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d%d%d", &n, &m, &k) != EOF) {
		dinic_init();
		int s = n + m;
		int t = s + 1;
		int sum1 = 0, sum2 = 0;
		for(int i = 0; i < n; i++) {
			int x;
			scanf("%d", &x);
			addEdge(s, i, x);
			sum1 += x;
		}
		for(int i = 0; i < m; i++) {
			int x;
			scanf("%d", &x);
			addEdge(i + n, t, x);
			sum2 += x;
		}
		if(sum1 != sum2) {
			puts("Impossible");
			continue;
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				id[i][j] = eh + 1;
				addEdge(i, j + n, k);
			}
		}
		int res = dinic(s, t);
		if(res != sum1) {
			puts("Impossible");
			continue;
		}
		std::memset(vis2, 0, sizeof (int) * ( n + m + 4));
		int f = 1;
		for(int i = 0; i < n + m + 2; i++) {
			if(!vis2[i]) {
				tm++;
				if(!dfs1(i)) {
					f = 0;
					break;
				}
			}
		}
		if(!f) puts("Not Unique");
		else {
			puts("Unique");
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < m; j++) {
					printf("%d ", ES[id[i][j]].cap);
				}
				puts("");
			}
		}
	}
	return 0;
}
