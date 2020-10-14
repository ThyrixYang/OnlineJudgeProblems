#include <bits/stdc++.h>

using namespace std;
const int INF = 2e9;
const int MAXN = 2e5 + 3000;
const int maxn = 1e6 + 2000;

struct Node{
	int val,dist;
	int ls,rs;
}T[maxn];
int sz;
int rc[maxn],rh;
int getNode(){
	int o;
	if(rh!=0) o=rc[--rh];
	else o=++sz;
	T[o].ls=T[o].rs=T[o].dist=0;
	return o;
}
void merge(int &r1,int &r2){
	if(T[r1].val>T[r2].val) swap(r1,r2);
	if(r1==0){
		r1=r2;
		return;
	}
	if(r2==0) return;
	merge(T[r1].rs,r2);
	if(T[T[r1].rs].dist>T[T[r1].ls].dist) swap(T[r1].ls,T[r1].rs);
	T[r1].dist=T[T[r1].rs].dist+1;
}
int pop(int &root){
	int ans=T[root].val;
	merge(T[root].ls,T[root].rs);
	rc[rh++]=root;
	root=T[root].ls;
	return ans;
}
void insert(int &root,int x){
	int o=getNode();
	T[o].val=x;
	merge(root,o);
}
int Ts;
int n, m;
int h[MAXN];
int Left[MAXN], Right[MAXN];
int fa[MAXN];
int fl[MAXN], fr[MAXN];
int root[MAXN];
int X[MAXN], O[MAXN];
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
struct Point {
	int x, y;
	Point(int x = 0, int y = 0): x(x), y(y) {}
	bool operator < (const Point &C) const {
		return y < C.y;
	}
}z1[MAXN];
int zh;
int cas = 0;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> Ts;
	while(Ts--) {
		scanf("%d%d", &n, &m);
		rh = sz = 0;
		h[0] = h[n] = INF;
		for(int i = 1; i < n; i++) {
			scanf("%d", &h[i]);
		}
		for(int i = 1; i <= n; i++) {
			 Left[i] = h[i - 1];
			 Right[i] = h[i];
			 fa[i] = i;
			 fl[i] = i - 1, fr[i] = i + 1;
			 root[i] = 0;
			 O[i] = X[i] = 0;
		}
		zh = 0;
		int res = 0;
		for(int i = 0; i < m; i++) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			if(z == 1) {
				z1[zh++] = Point(x, y);
			} else {
				insert(root[x], y);
				res++;
			}
		}
		std::sort(z1, z1 + zh);
		for(int i = 0; i < zh; i++) {
			int x = z1[i].x, y = z1[i].y;
			x = find(x);
			O[x]++;
			if(y >= Left[x]) {
				int L = find(fl[x]);
				while(Left[x] <= y) {
					merge(root[x], root[L]);
					fl[x] = fl[L];
					Left[x] = Left[L];
					fa[L] = x;
					O[x] += O[L];
					X[x] += X[L];
					L = find(fl[x]);
				}
			}
			if(y >= Right[x]) {
				int R = find(fr[x]);
				while(Right[x] <= y) {
					merge(root[x], root[R]);
					fr[x] = fr[R];
					Right[x] = Right[R];
					O[x] += O[R];
					X[x] += X[R];
					fa[R] = x;
					R = find(fr[x]);
				}
			}
			while(root[x] && T[root[x]].val <= y) {
				pop(root[x]);
				X[x]++;
			}
			
			if(O[x] >= X[x]) {
				res += O[x] - X[x];
				O[x] = X[x] = 0;
			}
		}
		printf("Case #%d: %d\n", ++cas, res);
	}
	return 0;
}
