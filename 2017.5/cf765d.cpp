#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 3000;
int N;
int f[MAXN];
int dic[MAXN], dh;
int g[MAXN];
int ind[MAXN];
int check() {
	for(int i = 1; i <= N; i++) {
		if(f[i] != i) ind[f[i]]++;
	}
	queue<int> Q;
	for(int i = 1; i <= N; i++) {
		if(ind[i] == 0) {
			Q.push(i);
		}
	}
	int cnt = 0;
	while(!Q.empty()) {
		int v = Q.front();
		cnt++;
		Q.pop();
		ind[f[v]]--;
		if(ind[f[v]] == 0) {
			Q.push(f[v]);
		}
	}
	return cnt == N;
}
int main() {
	cin >> N;
	for(int i = 1; i <= N; i++) {
		scanf("%d", &f[i]);
		dic[dh++] = f[i];
	}
	sort(dic, dic + dh);
	dh = unique(dic, dic + dh) - dic;
	for(int i = 0; i < dh; i++) {
		g[dic[i]] = i + 1;
	}
	for(int i = 1; i <= N; i++) {
		if(g[i] == 0) {
			g[i] = g[f[i]];
		}
	}
	int res = 1;
	for(int i = 1; i <= N; i++) {
		if(dic[g[i] - 1] != f[i]) {
			res = 0;
			break;
		}
	}
	for(int i = 1; i <= dh; i++) {
		if(g[dic[i - 1]] != i) {
			res = 0;
			break;
		}
	}
	if(!res) {
		puts("-1");
		return 0;
	}
	cout << dh << endl;
	for(int i = 1; i <= N; i++) printf("%d ", g[i]);
	puts("");
	for(int i = 1; i <= dh; i++) printf("%d ", dic[i - 1]);
	return 0;
}
