#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
struct Node {
	int v, l, r, d, u;
}T[MAXN * MAXN];
int n, m, q;
int mat[MAXN][MAXN];
void linkh(int a, int b) {
	T[a].r = b;
	T[b].l = a;
}
void linkv(int a, int b) {
	T[a].d = b;
	T[b].u = a;
}
int a[MAXN][MAXN];
int sz = 0;
int main(){
	freopen("./in","r",stdin);
	std::cin >> n >> m >> q;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
	for(int i = 0; i <= n + 1; i++) {
		for(int j = 0; j <= m + 1; j++) { 
			a[i][j] = sz++;
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			T[a[i][j]].v = mat[i][j];
		}
	}
	for(int i = 0; i <= n + 1; i++) {
		for(int j = 1; j <= m + 1; j++) {
			linkh(a[i][j - 1], a[i][j]);
		}
	}
	for(int j = 0; j <= m + 1; j++) {
		for(int i = 1; i <= n + 1; i++) {
			linkv(a[i - 1][j], a[i][j]);
		}
	}
	while(q--) {
		int x1, y1, x2, y2, h, w;
		scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &h, &w);
		int p1 = a[x1 - 1][0];
		int p2 = a[x2 - 1][0];
		for(int i = 1; i <= y1; i++) p1 = T[p1].r;
		for(int i = 1; i <= y2; i++) p2 = T[p2].r;
		for(int i = 0; i < w; i++) {
			int t1 = T[p1].d;
			int t2 = T[p2].d;
			linkv(p2, t1);linkv(p1, t2);
			p1 = T[p1].r; p2 = T[p2].r;
		}
		p1 = a[x1 + h - 1][0];
		p2 = a[x2 + h - 1][0];
		for(int i = 1; i <= y1; i++) p1 = T[p1].r;
		for(int i = 1; i <= y2; i++) p2 = T[p2].r;
		for(int i = 0; i < w; i++) {
			int t1 = T[p1].d;
			int t2 = T[p2].d;
			linkv(p2, t1);linkv(p1, t2);
			p1 = T[p1].r; p2 = T[p2].r;
		}
		p1 = a[0][y1 - 1];
		p2 = a[0][y2 - 1];
		for(int i = 1; i <= x1; i++) p1 = T[p1].d;
		for(int i = 1; i <= x2; i++) p2 = T[p2].d;
		for(int i = 0; i < h; i++) {
			int t1 = T[p1].r;
			int t2 = T[p2].r;
			linkh(p1, t2); linkh(p2, t1);
			p1 = T[p1].d, p2 = T[p2].d;
		}
		p1 = a[0][y1 + w - 1];
		p2 = a[0][y2 + w - 1];
		for(int i = 1; i <= x1; i++) p1 = T[p1].d;
		for(int i = 1; i <= x2; i++) p2 = T[p2].d;
		for(int i = 0; i < h; i++) {
			int t1 = T[p1].r;
			int t2 = T[p2].r;
			linkh(p1, t2); linkh(p2, t1);
			p1 = T[p1].d, p2 = T[p2].d;
		}
	}
	for(int i = 1; i <= n; i++) {
		int p = a[i][0];
		for(int j = 1; j <= m; j++) {
			p = T[p].r;
			printf("%d ", T[p].v);
		}
		puts("");
	}
	return 0;
}
