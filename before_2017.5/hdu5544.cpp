#include <bits/stdc++.h>

template <class T>
inline bool scan_d(T &ret) {
	char c;
	int sgn;
	if(c=getchar(),c==EOF) return 0;
	while(c!='-'&&(c<'0'||c>'9')) c=getchar();
	sgn=(c=='-')?-1:1;
	ret=(c=='-')?0:(c-'0');
	while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');
	ret*=sgn;
	return 1;
}
inline void out(int x) {
	if(x>9) out(x/10);
	putchar(x%10+'0');
}
const int MAXN = 1e5 + 300;
const int MAXE = 2e5 + 300;
struct edge {
	int to, next;
	long long w;
}E[MAXE];
int head[MAXN], eh;
void addEdge(int from, int to, long long w) {
	E[eh].to = to, E[eh].w = w, E[eh].next = head[from];
	head[from] = eh++;
}
long long A[MAXE], ah;
int vis[MAXN];
long long val[MAXN];
void dfs(int v = 1, long long x = 0) {
	val[v] = x;
	vis[v] = 1;
	for(int i = head[v]; i != -1; i = E[i].next) {
		int u = E[i].to;
		long long w = E[i].w;
		if(vis[u]) {
			if(w ^ val[v] ^ val[u]) A[ah++] = (w ^ val[v] ^ val[u]);
		}
		else dfs(u, x ^ w);
	}
}
int T, cas = 0;
int N, M;
int main() {
	freopen("in", "r", stdin);
	scan_d(T);
	while(T--) {
		printf("Case #%d: ", ++cas);
		scan_d(N);scan_d(M);
		std::memset(head, -1, sizeof (int) * (N + 3));
		std::memset(vis, 0, sizeof (int) * (N + 3));
		ah = eh = 0;
		for(int i = 0; i < M; i++) {
			long long x, y, z;
			scan_d(x);
			scan_d(y);
			scan_d(z);
			addEdge(x, y, z);
			addEdge(y, x, z);
		}
		dfs();
		long long ans = 0;
		long long e = 0;
		for(long long t = (1ll << 60); t > 0; t /= 2) {
			long long x = -1;
			int j = 0;
			for(; j < ah; j++) {
				if(A[j] & t) {
					x = A[j];
					break;
				}
			}
			if(x != -1) {
				if(!(e & t)) e ^= x;
				ans = std::max(ans, e);
				for(; j < ah; j++) {
					if(A[j] & t) {
					 	A[j] ^= x;
					}
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}