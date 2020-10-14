#include <bits/stdc++.h>

using namespace std;
struct Reader{
	static const int MSIZE=65536;
	char buffer[MSIZE],c;
	int l,r;
	Reader():l(0),r(0){}
	char readchar(){
		if(l==r){
			l=0;
			r=fread(buffer,1,MSIZE,stdin);
			//
			buffer[r]=0;
			r++;///注意此处是修改过的
			//
		}
		return buffer[l++];
	}
	int readint(){
		c=readchar();
		while(!isdigit(c)) c=readchar();
		int res=0;
		while(isdigit(c)) res=res*10+c-'0',c=readchar();
		return res;
	}
}R;

const int MAXN = 1005;
const int INF = 0x3f3f3f3f;
vector<int> G[MAXN];
vector<int> G2[2005];
int uN;
int Mx[MAXN],My[MAXN];
int dx[MAXN],dy[MAXN];
int dis;
bool used[MAXN];
bool SearchP(){
    queue<int>Q;
    dis = INF;
	memset(dx,-1,sizeof(dx));
	memset(dy,-1,sizeof(dy));
    for(int i = 0 ; i < uN; i++){
        if(Mx[i] == -1){
            Q.push(i);
            dx[i] = 0;
        }
    }
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        if(dx[u] > dis)break;
        int sz = G[u].size();
        for(int i = 0;i < sz;i++){
            int v = G[u][i];
            if(dy[v] == -1){
                dy[v] = dx[u] + 1;
                if(My[v] == -1)dis = dy[v];
                else{
                    dx[My[v]] = dy[v] + 1;
                    Q.push(My[v]);
                }
            }
        }
    }
    return dis != INF;
}
bool DFS(int u){
    int sz = G[u].size();
    for(int i = 0;i < sz;i++){
        int v = G[u][i];
        if(!used[v] && dy[v] == dx[u] + 1){
            used[v] = true;
            if(My[v] != -1 && dy[v] == dis)continue;
            if(My[v] == -1 || DFS(My[v])){
                My[v] = u;
                Mx[u] = v;
                return true;
            }
        }
    }
    return false;
}
int MaxMatch(){
    int res = 0;
    memset(Mx,-1,sizeof(Mx));
    memset(My,-1,sizeof(My));
    while(SearchP()){
        memset(used,false,sizeof(used));
        for(int i = 0;i < uN;i++){
            if(Mx[i] == -1 && DFS(i))
                res++;
        }
    }
    return res;
}
int col[2005];
int match[2005];
int N, M, K;
int main() {
	freopen("./in", "r", stdin);
	N = R.readint();
	M = R.readint();
	K = R.readint();
	uN = N;
	for(int i = 0; i < K; i++) {
		int x, y;
		x = R.readint();
		y = R.readint();
		x--, y--;
		G2[y + N].push_back(x);
		G2[x].push_back(y + N);
		G[x].push_back(y);
	}
	int cnt = MaxMatch();
	for(int i = 0; i < N; i++) {
		if(Mx[i] == -1) match[i] = -1;
		else match[i] = Mx[i] + N;
	}
	for(int i = 0; i < M; i++) {
		match[i + N] = My[i];
	}
	std::queue<int> Q;
	for(int i = 0; i < N + M; i++) {
		if(match[i] == -1) {
			Q.push(i);
			col[i] = -1;
		}
	}
	while(!Q.empty()) {
		int v = Q.front();
		Q.pop();
		if(col[v] == 1) {
			if(!col[match[v]]) {
				col[match[v]] = -1;
				Q.push(match[v]);
			}
		} else {
			for(int u: G2[v]) {
				if(!col[u]) {
					col[u] = 1;
					Q.push(u);
				}
			}
		}
	}
	for(int i = 0; i < N; i++) {
		if(col[i] == -1) printf("N");
		else if(col[i] == 1) printf("A");
		else printf("E");
	}
	puts("");
	for(int i = N; i < N + M; i++) {
		if(col[i] == -1) printf("N");
		else if(col[i] == 1) printf("A");
		else printf("E");
	}
	puts("");
	return 0;
}
