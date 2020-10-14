#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 300;
const int MAXE = 4e6;
struct edge {
	 int to, cap, next;
}E[MAXE];
int head[MAXN], eh;
void addEdge(int from, int to, int cap) {
	E[eh].to = to, E[eh].cap = cap, E[eh].next = head[from];
	head[from] = eh++;
	E[eh].to = from, E[eh].cap = 0, E[eh].next = head[to];
	head[to] = eh++;
}
int vis[MAXN], tmm;
int que[MAXE], front, back;
int dis[MAXN];
int bfs(int s, int t) {
	tmm++;
	front = back = 0;
	que[back++] = s;
	dis[s] = 0;
	vis[s] = tmm;
	while(front < back) {
		int v = que[front++];
		for(int i = head[v]; i != -1; i = E[i].next) {
			int u = E[i].to;
			if(!E[i].cap) continue;
			if(vis[u] != tmm) {
				vis[u] = tmm;
				dis[u] = dis[v] + 1;
				que[back++] = u;
			}
		}
	}
	return vis[t] == tmm;
}
int iter[MAXN];
int dfs(int v, int t, int f) {
	if(v == t) return f;
	int c = 0;
	for(int &i = iter[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(!E[i].cap || dis[u] <= dis[v]) continue;
		int d = dfs(u, t, std::min(f - c, E[i].cap));
		c += d;
		E[i].cap -= d;
		E[i ^ 1].cap += d;
		if(c == f) return f;
	}
	return c;
}
int dinic(int s, int t) {
	int flow = 0;
	for(;;) {
		if(!bfs(s, t)) return flow;
		for(int i = 0; i < MAXN; i++) iter[i] = head[i];
		int d;
		while((d = dfs(s, t, 1e9)) != 0) flow += d;
	}
	return flow;
}
void clearGraph() {
	eh = 0;
	std::memset(head, -1, sizeof head);
}

int dicx[MAXN], dhx;
int dicy[MAXN], dhy;
#define idxx(x) (std::lower_bound(dicx, dicx + dhx, x) - dicx)
#define idxy(y) (std::lower_bound(dicy, dicy + dhy, y) - dicy)

int N, M, R, B, S, T;
int point[MAXN][2];
int limx[MAXN], limy[MAXN];
int ins[MAXN];
int cntx[MAXN], cnty[MAXN];
int tol;
int ide[MAXN];
void addEdge2(int from, int to, int low, int up) {
	//std::cout << from << " " << to << " " << low << " " << up << std::endl;
	if(up - low > 0) addEdge(from, to, up - low);
	if(low > 0) {
		ins[to] += low;
		ins[from] -= low;
		tol += low;
	}
}
int main() {
	freopen("./in", "r", stdin);
	clearGraph();
	std::memset(limx, 0x3f, sizeof limx);
	std::memset(limy, 0x3f, sizeof limy);
	scanf("%d%d", &N, &M);
	scanf("%d%d", &R, &B);
	for(int i = 0; i < N; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		point[i][0] = x, point[i][1] = y;
		dicx[dhx++] = x;
		dicy[dhy++] = y;
	}
	std::sort(dicx, dicx + dhx);
	std::sort(dicy, dicy + dhy);
	dhx = std::unique(dicx, dicx + dhx) - dicx;
	dhy = std::unique(dicy, dicy + dhy) - dicy;
	for(int i = 0; i < M; i++) {
		int t, l, d;
		scanf("%d%d%d", &t, &l, &d);
		if(t == 1) {
			int id = idxx(l);
			if(dicx[id] != l) continue;
			limx[id] = std::min(limx[id], d);
		} else {
			int id = idxy(l);
			if(dicy[id] != l) continue;
			limy[id] = std::min(limy[id], d);
		}
	}
	int ss = dhx + dhy + 3;
	int tt = ss + 1;
	S = tt + 1;
	T = S + 1;
	addEdge(tt, ss, 1e9);
	for(int i = 0; i < N; i++) {
		int x = idxx(point[i][0]);
		int y = idxy(point[i][1]);
		cntx[x]++;
		cnty[y]++;
		addEdge(x, dhx + y, 1);
		//std::cout << x << " " << dhx + y << std::endl;
		ide[i] = eh - 1;
	}
	for(int i = 0; i < dhx; i++) {
		int up = (limx[i] + cntx[i]) / 2;
		int low = std::max(0, (cntx[i] - limx[i] + 1) / 2);
		addEdge2(ss, i, low, up);
		if(limx[i] == 0 && cntx[i] % 2 != 0) {
			puts("-1");
			return 0;
		}
	}
	for(int i = 0; i < dhy; i++) {
		int up = (limy[i] + cnty[i]) / 2;
		int low = std::max(0, (cnty[i] - limy[i] + 1) / 2);
		addEdge2(i + dhx, tt, low, up);
		if(limy[i] == 0 && cnty[i] % 2 != 0) {
			puts("-1");
			return 0;
		}
	}
	for(int i = 0; i < dhx + dhy; i++) {
		if(ins[i] > 0) addEdge(S, i, ins[i]);//, printf("S %d %d\n", i, ins[i]);
		else if(ins[i] < 0) addEdge(i, T, -ins[i]);//, printf("%d T %d\n", i, -ins[i]);
	}
	addEdge(ss, T, -ins[ss]);
	addEdge(S, tt, ins[tt]);
	int res = dinic(S, T);
	//printf("%d\n", res);
	if(res != tol) {
		puts("-1");
		return 0;
	}
	long long cc = E[1].cap;
	E[1].cap = E[0].cap = 0;
	cc += dinic(ss, tt);
	char cr = 'r', cb = 'b';
	if(R > B) std::swap(R, B), std::swap(cr, cb);
	std::cout << (long long)cc * R + (N - cc) * (long long)B << std::endl;
	for(int i = 0; i < N; i++) {
		if(E[ide[i]].cap) printf("%c", cr);
		else printf("%c", cb);
	}
	return 0;
}
