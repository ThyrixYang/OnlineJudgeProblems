#include <bits/stdc++.h>

const long long MOD = 1e9 + 7;
const int SZ = 2;
const int MAXO = 1e6;
const int MAXN = 2e5;
struct matrix {
	long long a[SZ][SZ];
	matrix() {std::memset(a, 0, sizeof a);}
	friend matrix operator * (const matrix &A, const matrix &B);
	void I(){
		a[0][0] = a[1][1] = 1;
		a[0][1] = a[1][0] = 0;
	}
};
matrix operator * (const matrix &A, const matrix &B) {
	matrix ans;
	for(int i = 0; i < SZ; i++) {
		for(int j = 0; j < SZ; j++) {
			for(int k = 0; k < SZ; k++) {
				ans.a[i][j] += A.a[i][k] * B.a[k][j] % MOD;
			}
			ans.a[i][j] %= MOD;
		}
	}
	return ans;
}
matrix qpow(matrix a, long long p) {
	matrix ans;
	ans.I();
	while(p > 0) {
		if(p & 1) ans = ans * a;
		a = a * a;
		p >>= 1;
	}
	return ans;
}
#define chl ((o << 1))
#define chr ((o << 1) | 1)
#define mi ((l + r) >> 1)
matrix fibt;
matrix mval[MAXO];
long long val[MAXO][2];
long long a[MAXN];
void multi(int o, matrix x) {
	long long t = val[o][0] * x.a[0][0] % MOD + val[o][1] * x.a[0][1] % MOD;
	t %= MOD;
	val[o][1] = val[o][0] * x.a[1][0] % MOD + val[o][1] * x.a[1][1] % MOD;
	val[o][1] %= MOD;
	val[o][0] = t;
}
void up(int o, int l, int r) {
	if(r - l <= 1) return;
	val[o][0] = (val[chl][0] + val[chr][0]) % MOD;
	val[o][1] = (val[chl][1] + val[chr][1]) % MOD;
}
void push(int o, int l, int r) {
	if(r - l > 1) {
		multi(chl, mval[o]);
		multi(chr, mval[o]);
		mval[chl] = mval[chl] * mval[o];
		mval[chr] = mval[chr] * mval[o];
	}
	mval[o].I();
}
void build(int o, int l, int r) {
	mval[o].I();
	if(r - l <= 1) {
		matrix t = qpow(fibt, a[l] - 1);
		val[o][0] = t.a[0][0];
		val[o][1] = t.a[1][0];
		return;
	}
	build(chl, l, mi);
	build(chr, mi, r);
	up(o, l, r);
}
void update(int o, int a, int b, int l, int r, matrix x) {
	if(a >= r || l >= b) return;
	if(l >= a && r <= b) {
		mval[o] = mval[o] * x;
		multi(o, x);
		return;
	}
	push(o, l, r);
	update(chl, a, b, l, mi, x);
	update(chr, a, b, mi, r, x);
	up(o, l, r);
}
long long query(int o, int a, int b, int l, int r) {
	if(a >= r || b <= l) return 0;
	if(l >= a && r <= b) return val[o][0];
	push(o, l, r);
	return (query(chl, a, b, l, mi) + query(chr, a, b, mi, r)) % MOD;
}
int N, M;
int main() {
	freopen("./in", "r", stdin);
	fibt.a[0][0] = fibt.a[0][1] = fibt.a[1][0] = 1;
	std::cin >> N >> M;
	for(int i = 1; i <= N; i++) {
		scanf("%lld", &a[i]);
	}
	build(1, 1, N + 1);
	while(M--) {
		int t;
		scanf("%d", &t);
		if(t == 1) {
			int l, r, x;
			scanf("%d%d%d", &l, &r, &x);
			matrix tr = qpow(fibt, x);
			update(1, l, r + 1, 1, N + 1, tr);
		} else {
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%lld\n", query(1, l, r + 1, 1, N + 1));
		}
	}
	return 0;
}
