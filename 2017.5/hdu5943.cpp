#include <bits/stdc++.h>

using namespace std;
#define pb push_back
const int maxn=300;
vector<int> G[maxn];
int n,m;
int match[maxn];
bool used[maxn];
inline void addedge(int a,int b){
	G[a].pb(b);
	G[b].pb(a);
}
bool dfs(int v){
	used[v]=1;
	for(int i=0;i<G[v].size();i++){
		int u=G[v][i],w=match[u];
		if(w<0||!used[w]&&dfs(w)){
			match[v]=u;
			match[u]=v;
			return 1;
		}
	}
	return 0;
}
inline int bi_match(){
	int res=0;
	memset(match,-1,sizeof match);
	for(int i=0;i<maxn;i++){
		if(match[i]==-1){
			memset(used,0,sizeof used);
			if(dfs(i)){
				res++;
			}
		}
	}
	return res;
}
inline void clear(){
	for(int i=0;i<maxn;i++){
		G[i].clear();
	}
}
int T, cas = 0;
int N, S;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		printf("Case #%d: ", ++cas);
		scanf("%d%d", &N, &S);
		clear();
		int len = 100;
		len = min(len, S);
		len = min(len, N);
		for(int i = 1; i <= len; i++) {
			for(int j = S + N; j > S + N - len; j--) {
				int v = j - (S + N - len) + len;
				if(j % i == 0) addedge(i, v);
			}
		}
		int mt = bi_match();
		if(mt == len) puts("Yes");
		else puts("No");
	}
	return 0;
}
