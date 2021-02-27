#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6;
int N;
vector<int> G[MAXN];
int down[MAXN], up[MAXN];
void dfs0(int v, int f = -1) {
	int has = 0;
	int len = -2;
	for(int i = 0; i < (int) G[v].size(); i++) {
		int u = G[v][i];
		if(u == f) continue;
		has = 1;
		dfs0(u, v);
		if(down[u] == -1 || len == -1) len = -1;
		else if(len == -2) len = down[u] + 1;
		else if(len == down[u] + 1) len = down[u] + 1;
		else len = -1;
	}
	if(has == 0) len = 0;
	down[v] = len;
}
int ans = 1e9;
void dfs1(int v, int lenup = 0, int f = -1) {
	//printf("%d %d\n", v, lenup);
	map<int, vector<int> > M;
	map<int, vector<int> > :: iterator it;
	if(lenup != 0) M[lenup].push_back(f);
	for(int i = 0; i < (int) G[v].size(); i++) {
		int u = G[v][i];
		if(u == f) continue;
		if(down[u] != -1) M[down[u] + 1].push_back(u);
		else M[-1].push_back(u);
	}
	if(M.find(-1) == M.end()) {
		if(M.size() == 1) {
			it = M.begin();
			ans = min(ans, it->first);
		} else if(M.size() == 2) {
			it = M.begin();
			int sum = it->first;
			it++;
			sum += it->first;
			ans = min(ans, sum);
		}
	}
	if(M.find(-1) != M.end() && M[-1].size() == 1) {
		it = M.find(-1);
		vector<int> &V = it->second;
		int u = V[0];
		if(u == f) return;
		if(M.size() == 2) {
			it++;
			dfs1(u, it->first + 1, v);
		}
		if(M.size() == 1 && M[-1].size() == 1) {
			dfs1(u, 1, v);
		}
	} else {
		if(M.size() == 2) {
			it = M.begin();
			if(it->second.size() == 1 && it->second[0] != f) {
				int u = it->second[0];
				it++;
				dfs1(u, it->first + 1, v);
			} else {
				int l = it->first;
				it++;
				if(it->second.size() == 1 && it->second[0] != f) {
					int u = it->second[0];
					dfs1(u, l + 1, v);
				}
			}
		} else if(M.size() == 1) {
			it = M.begin();
			for(int i = 0; i < (int) G[v].size(); i++) {
				int u = G[v][i];
				if(u == f) continue;
				dfs1(u, it->second.size() == 1 ? 1 : it->first + 1, v);
			}
		}
	}
}
int main() {
	freopen("./in.txt", "r", stdin);

	cin >> N;
	for(int i = 0; i < N - 1; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	dfs0(1);
	/*
	for(int i = 1; i <= N; i++) {
		printf("%d %d\n", i, down[i]);
	}
	puts("");*/
	dfs1(1);
	if(ans < 1e8) {
		while(ans % 2 == 0) ans /= 2;
		cout << ans << endl;
	}
	else cout << -1 << endl;
	return 0;
}
