#include <bits/stdc++.h>

using namespace std;

struct Mat {
	int a[5][5];
	Mat() {
		memset(a, 0x3f, sizeof a);
	}
};
Mat operator ^ (const Mat &A,const Mat &B) {
	Mat res;
	for(int i = 0; i < 5; i++) {
		for(int j = i; j < 5; j++) {
			for(int k = i; k <= j; k++) {
				res.a[i][j] = min(res.a[i][j], A.a[i][k] + B.a[k][j]);
			}
		}
	}
	return res;
}
const int MAXN = 2e5 + 30;
const int MAXO = MAXN * 4;
int N, Q;
char s[MAXN];
Mat dp[MAXO];
#define mi ((r + l) >> 1)
#define chl ((o << 1))
#define chr ((o << 1) | 1)
void build(int o, int l, int r) {
	if(r - l <= 1) {
		for(int i = 0; i < 5; i++) dp[o].a[i][i] = 0;
		if(s[l] == '1') {
			dp[o].a[2][2] = 1;
			dp[o].a[2][3] = 0;
		} else if(s[l] == '2') {
			dp[o].a[0][0] = 1;
			dp[o].a[0][1] = 0;
		} else if(s[l] == '0') {
			dp[o].a[1][1] = 1;
			dp[o].a[1][2] = 0;
		} else if(s[l] == '7') {
			dp[o].a[3][4] = 0;
			dp[o].a[3][3] = 1;
		} else if(s[l] == '6') {
			dp[o].a[4][4] = dp[o].a[3][3] = 1;
		} else {

		}
		return;
	}
	build(chl, l, mi);
	build(chr, mi, r);
	dp[o] = dp[chl] ^ dp[chr];
	return;
}
Mat query(int o, int a, int b, int l, int r) {
	if(l >= a && r <= b) return dp[o];
	if(b <= mi) return query(chl, a, b, l, mi);
	if(a >= mi) return query(chr, a, b, mi, r);
	return query(chl, a, b, l, mi) ^ query(chr, a, b, mi, r);
}
int main() {
	freopen("../Data/stdin", "r", stdin);
	cin >> N >> Q;
	scanf("%s", s);
	build(1, 0, N);
	for(int cas = 0; cas < Q; cas++) {
		int x, y;
		scanf("%d%d", &x, &y);
		Mat res = query(1, x - 1, y, 0, N);
		if(res.a[0][4] > 1e6) puts("-1");
		else printf("%d\n", res.a[0][4]);
	}
	return 0;
}
