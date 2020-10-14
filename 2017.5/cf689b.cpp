#include <bits/stdc++.h>

const int maxn = 1e6;
std::vector<int> G[maxn];
int n;
int dis[maxn];
int main() {
	std::cin >> n;
	for(int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		G[i].push_back(x);
		if(i < n) G[i].push_back(i + 1),G[i + 1].push_back(i);
	}
	memset(dis, 0x3f, sizeof dis);
	std::queue<int> Q;
	dis[1] = 0;
	Q.push(1);
	while(!Q.empty()){
		int v = Q.front();
		Q.pop();
		for(int i = 0; i < G[v].size(); i++) {
			int u = G[v][i];
			if(dis[u] > dis[v] + 1){
				dis[u] = dis[v] + 1;
				Q.push(u);
			}
		}
	}
	for(int i = 1; i <= n; i++) printf("%d ",dis[i]);
	return 0;
}
