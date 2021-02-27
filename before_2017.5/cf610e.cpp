#include <bits/stdc++.h>

#define ls (o << 1)
#define rs ((o << 1) | 1)
#define mid ((r + l) >> 1)

const int maxn = 8e5;
char s[maxn];
int n, m, k;
int cnt[maxn][10][10];
int lab[maxn], chg[maxn];
int f[maxn], t[maxn];

void push_up(int o, int l, int r) {
	for(int i = 0; i < k; i++) {
		for(int j = 0; j < k; j++) {
			cnt[o][i][j] = cnt[ls][i][j] + cnt[rs][i][j];
		}
	}
	cnt[o][t[ls]][f[rs]]++;
	f[o] = f[ls];
	t[o] = t[rs];
}

void push_down(int o, int l, int r) {
	if(!lab[o]) return ;
	lab[ls] = lab[rs] = 1;
	lab[o] = 0;
	chg[ls] = chg[rs] = chg[o];
	memset(cnt[ls], 0, sizeof(int) * 100);
	memset(cnt[rs], 0, sizeof(int) * 100);
	int c = chg[o];
	cnt[ls][c][c] = mid - l -1;
	cnt[rs][c][c] = r - mid -1;
	f[ls] = t[ls] = f[rs] = t[rs] = c;
}

void build(int o, int l, int r) {
	if(r - l == 1) {
		int c = s[l] - 'a';
		f[o] = t[o] = c;
		return ;
	}
	build(ls, l, mid);
	build(rs, mid, r);
	push_up(o, l, r);
}

void change(int o, int a, int b, int l, int r, int c) {
	if(a >= r || b <= l) return;
	if(l >= a && r <= b) {
		chg[o] = c;
		memset(cnt[o], 0, sizeof(int) * 100);
		cnt[o][c][c] = r - l - 1;
		lab[o] = 1;
		f[o] = t[o] = c;
		return ;
	}
	push_down(o, l, r);
	change(ls, a, b, l, mid, c);
	change(rs, a, b, mid, r, c);
	push_up(o, l, r);
}

char ss[20];
int main() {
	std::cin >> n >> m >> k;
	scanf("%s", s + 1);
	build(1, 1, n + 1);
	while(m--) {
		int tt;
		scanf("%d", &tt);
		if(tt == 1) {
			int x, y;
			scanf("%d%d%s", &x, &y, ss);
			int z = ss[0] - 'a';
			change(1, x, y + 1, 1, n + 1, z);
		}else {
			scanf("%s", ss);
			int ans = 0;
			for(int i = 0; i < k; i++) {
				for(int j = 0; j <= i; j++) {
					ans += cnt[1][ss[i] - 'a'][ss[j] - 'a'];
				}
			}
			printf("%d\n", ans + 1);
		}
	}
	return 0;
}
