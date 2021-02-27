#include <bits/stdc++.h>

const int MAXO = 2e7;
const int MAXN = 1e6;
struct Point {
	int x, y;
	void in() {
		scanf("%d%d", &x, &y);
	}
	bool operator < (const Point &C) const {
		if(x != C.x) return x < C.x;
		return y < C.y;
	}
	bool operator == (const Point &C) const {
		return x == C.x && y == C.y;
	}
}p[MAXN];
struct Node {
	int val, ls, rs;
}T[MAXO];
const int MAXV = 5e4 + 30;
int root[MAXV];
int sz;
#define mi ((l + r) >> 1)
void add(int &o, int l, int r, int x) {
	T[++sz] = T[o];
	o = sz;
	T[o].val++;
	if(r - l <= 1) return;
	if(x < mi) add(T[o].ls, l, mi, x);
	else add(T[o].rs, mi, r, x);
}
int sum(int o1, int o2, int a, int b, int l, int r) {
	if(a >= b) return 0;
	if(a >= r || b <= l) return 0;
	if(l >= a && r <= b) return T[o2].val - T[o1].val;
	return sum(T[o1].ls, T[o2].ls, a, b, l, mi) + 
		sum(T[o1].rs, T[o2].rs, a, b, mi, r);
}
int n;
int l[MAXV], d[MAXV];
int main() {
	freopen("./in", "r", stdin);
	while(std::cin >> n) {
		sz = 0;
		if(n == 0) break;
		for(int i = 0; i < n; i++)
			p[i].in();
		std::sort(p, p + n);
		n = std::unique(p, p + n) - p;
		std::memset(l, 0, sizeof l);
		std::memset(d, 0, sizeof d);
		bool F = 1;
		int r = 0;
		for(int i = 0; i < n; i++) { 
			while(r < p[i].x) {
				root[r + 1] = root[r];
				r++;
			}
			int res = sum(root[l[p[i].y]], root[p[i].x - 1],
					d[p[i].x] + 1, p[i].y, 0, MAXV);
			if(res) {
				F = 0;
				break;
			}
			l[p[i].y] = p[i].x;
			d[p[i].x] = p[i].y;
			add(root[p[i].x], 0, MAXV, p[i].y);
		}
		if(!F) {
			puts("NO");
			continue;
		}
		sz = 0;
		std::memset(l, 0, sizeof l);
		std::memset(d, 0, sizeof d);
		for(int i = 0; i < n; i++) p[i].x = MAXV - p[i].x - 3;
		std::sort(p, p + n);
		r = 0;
		for(int i = 0; i < n; i++) { 
			while(r < p[i].x) {
				root[r + 1] = root[r];
				r++;
			}
			int res = sum(root[l[p[i].y]], root[p[i].x - 1],
					d[p[i].x] + 1, p[i].y, 0, MAXV);
			if(res) {
				F = 0;
				break;
			}
			l[p[i].y] = p[i].x;
			d[p[i].x] = p[i].y;
			add(root[p[i].x], 0, MAXV, p[i].y);
		}
		if(!F) {
			puts("NO");
		}
		else {
			puts("YES");
		}
	}
	return 0;
}
