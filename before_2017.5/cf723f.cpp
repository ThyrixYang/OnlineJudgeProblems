#include <bits/stdc++.h>

const int MAXN = 1e6;
struct edge {
	int u, v;
}E[MAXN];
int N, M;
std::vector<int> use;
int S, T, ds, dt;
int fa[MAXN];
int cs[MAXN], ct[MAXN];
int cst;
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
int fuc(int x) {
	if(x == S || x == T) return 1;
	return 0;
}
void upd(int &a, int b) {
	if(a == 0) a = b;
}
int blk[MAXN], bh;
std::vector<int> csb, ctb, cstb;
int main() {
	freopen("./in", "r", stdin);
	for(int i = 0; i < MAXN; i++) fa[i] = i;
	std::cin >> N >> M;
	for(int i = 1; i <= M; i++) {
		scanf("%d%d", &E[i].u, &E[i].v);
	}
	std::cin >> S >> T >> ds >> dt;
	for(int i = 1; i <= M; i++) {
		if(fuc(E[i].u) && fuc(E[i].v)) {
			cst = i;
		} else if(fuc(E[i].u)) {
			if(E[i].u == S) {
				cs[find(E[i].v)] = i;
			} else {
				ct[find(E[i].v)] = i;
			}
		} else if(fuc(E[i].v)) {
			if(E[i].v == S) cs[find(E[i].u)] = i;
			else ct[find(E[i].u)] = i;
		} else {
			if(find(E[i].u) == find(E[i].v)) continue;
			upd(cs[find(E[i].u)], cs[find(E[i].v)]);
			upd(ct[find(E[i].u)], ct[find(E[i].v)]);
			fa[find(E[i].v)] = find(E[i].u);
			use.push_back(i);
		}
	}
	for(int i = 1; i <= N; i++) {
		blk[bh++] = find(i);
	}
	std::sort(blk, blk + bh);
	bh = std::unique(blk, blk + bh) - blk;
	for(int i = 0; i < bh; i++)  {
		if(cs[i] != 0 && ct[i] != 0) {
			cstb.push_back(i);
		} else if(cs[i] != 0) {
			csb.push_back(i);
		} else if(ct[i] != 0) {
			ctb.push_back(i);
		} else {
			puts("No");
			return 0;
		}
	}
	if(csb.size() > ds || ctb.size() > dt) {
		puts("No");
		return 0;
	}
	
	return 0;
}
