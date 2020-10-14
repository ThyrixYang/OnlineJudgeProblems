#include <bits/stdc++.h>

const int MAXN = 1e5 + 200;
const int MAXM = MAXN * 6;

struct any {
	int d, val, v;
	any(int d = 0, int val = 0, int v = 0) :d(d), val(val), v(v) {}
	bool operator < (const any &C) const {
		if(d != C.d) return d < C.d;
		if(val != C.val) return val > C.val;
		return v < C.v;
	}
};
typedef std::pair<int, int> P;
struct edge {
	int to, w, next;
}E[MAXM];
int head[MAXN], eh;
int fa[MAXN], len[MAXN];
int val[MAXN];
int last[MAXN];
void addEdge(int from, int to, int w) {
	E[eh].to = to, E[eh].w = w, E[eh].next = head[from];
	head[from] = eh++;
}



int N;
/////////
int pre[20][MAXN];
int prel[20][MAXN];
int dep[MAXN];
void dfsx(int v, int f = 0, int d = 0) {
	dep[v] = d;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(u == f) continue;
		pre[0][u] = v;
		prel[0][u] = E[i].w;
		dfsx(u, v, d + 1);
	}
}
void lcaInit() {
	dfsx(1);
	 for(int k = 1; k < 20; k++) {
		 for(int i = 1; i <= N; i++) {
			 pre[k][i] = pre[k - 1][pre[k - 1][i]];
			 prel[k][i] = prel[k - 1][i] + prel[k - 1][pre[k - 1][i]];
		 }
	 }
}
int calDis(int a, int b) {
	if(a == b) return 0;
	if(dep[a] < dep[b]) std::swap(a, b);
	int ans = 0;
	for(int i = 19; i >= 0; i--) {
		if(dep[a] - dep[b] >= (1 << i)) {
			ans += prel[i][a];
			a = pre[i][a];
		}
	}
	if(a == b) return ans;
	for(int i = 19; i >= 0; i--) {
		if(pre[i][a] != pre[i][b]) {
			ans += prel[i][a];
			ans += prel[i][b];
			a = pre[i][a];
			b = pre[i][b];
		}
	}
	ans += prel[0][a] + prel[0][b];
	return ans;
}
////////
std::vector<any> V[MAXN];
int cut[MAXN], dis[MAXN];
void init() {
	std::memset(head, -1, sizeof (int) * (N + 3));
	std::memset(cut, 0, sizeof (int) * (N + 3));
	eh = 0;
	for(int i = 0; i < N + 3; i++) V[i].clear();
}
int count(int v, int f = 0, int d = 0) {
	int ans = 1;
	dis[v] = d;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(u == f || cut[u]) continue;
		ans += count(u, v, d + E[i].w);
	}
	return ans;
}
int cen, tol;
int dfs1(int v, int f = 0) {
	int maxs = 0;
	int ans = 1;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(u == f || cut[u]) continue;
		int d = dfs1(u, v);
		ans += d;
		maxs = std::max(maxs, d);
	}
	if(maxs <= tol / 2 && (tol - ans <= tol / 2)) {
		cen = v;
	}
	return ans;
}
void dfs2(int cen, int v, int f = 0, int d = 0) {
	V[cen].push_back(any(d, val[v], v));
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(u == f || cut[u]) continue;
		dfs2(cen, u, v, d + E[i].w);
	}
}
P getCenter(int s) {
	tol = count(s);
	dfs1(s);
	return P(cen, dis[cen]);
}
void deal(std::vector<any> &v, int &h) {
	std::sort(v.begin(), v.end());
	h = 0;
	for(int i = 1; i < (int) v.size(); i++) {
		if(v[i].d <= v[h].d) continue;
		if(v[i].val > v[h].val || (v[i].val == v[h].val && v[i].v < v[h].v)) {
			v[++h] = v[i];
		}
	}
}
void build(int v) {
	cut[v] = 1;
	dfs2(v, v);
	deal(V[v], last[v]);
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		if(cut[u]) continue;
		P tmp = getCenter(u);
		fa[tmp.first] = v;
		len[tmp.first] = tmp.second + E[i].w;
		build(tmp.first);
	}
}
P query(int s, int u, int R) {
	int d = calDis(s, u);
	if(u == 0) return P(1e9, 1e9);
	int l = -1, r = last[u] + 1;
	P ans(1e9, 1e9);
	while(r - l > 1) {
		int mid = (r + l) >> 1;
		if(V[u][mid].d <= R - d) l = mid;
		else r = mid;
	}
	if(l >= 0) ans = std::min(ans, P(-V[u][l].val, V[u][l].v));
	ans = std::min(ans, query(s, fa[u], R));
	return ans;
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N;
	init();
	for(int i = 1; i <= N; i++) scanf("%d", &val[i]);
	for(int i = 0; i < N - 1; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		addEdge(x, y, z);
		addEdge(y, x, z);
	}
	lcaInit();
	P tmp = getCenter(1);
	fa[tmp.first] = 0;
	build(tmp.first);
	int Q;
	scanf("%d", &Q);
	while(Q--) {
		int u, r;
		scanf("%d%d", &u, &r);
		printf("%d\n", query(u, u, r).second);
	}
	return 0;
}
