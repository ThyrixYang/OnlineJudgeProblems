#include <bits/stdc++.h>

const long long MOD = 268435456;
const int MAXN = 1e5 + 30;
const int MAXO = MAXN * 30;
int ch[MAXO][2];
int val[MAXO];
int sz;
int T;
int N, X, L;
int A[MAXN];
int suf[MAXN];
int P, Q;
int bs[30];
int bx[30];
int dp[MAXN];
void getbs(int x) {
	for(int i = 0; i < 30; i++) {
		bs[i] = (x & 1);
		x >>= 1;
	}
	std::reverse(bs, bs + 30);
}
void insert(int x, int value) {
	getbs(x);
	int v = 0;
	for(int i = 0; i < 30; i++) {
		if(ch[v][bs[i]]  == 0) {
			ch[v][bs[i]] = ++sz;
			std::memset(ch[sz], 0, sizeof ch[sz]);
			val[sz] = -1;
		}
		v = ch[v][bs[i]];
		val[v] = std::max(val[v], value);
	}
}
int Path[30];
void del(int x) {
	getbs(x);
	int v = 0;
	for(int i = 0; i < 30; i++) {
		v = ch[v][bs[i]];
		Path[i] = v;
	}
	val[v] = -1;
	for(int i = 28; i >= 0; i--) {
		int u = Path[i];
		val[u] = std::max(val[ch[u][0]], val[ch[u][1]]);
	}
}
int query(int x) {
	getbs(x);
	int ans = 0;
	int v = 0;
	for(int i = 0; i < 30; i++) {
		if(ch[v][0] != 0 && (bs[i] < bx[i]) && val[ch[v][0]] >= 0) {
			ans = std::max(ans, val[ch[v][0]] + 1);
		}
		if(ch[v][1] != 0 && ((bs[i] ^ 1) < bx[i]) && val[ch[v][1]] >= 0) {
			ans = std::max(ans, val[ch[v][1]] + 1);
		}
		if(ch[v][0] != 0 && (bs[i] == bx[i])) {
			v = ch[v][0];
		} else if(ch[v][1] != 0 && ((bs[i] ^ 1) == bx[i])) {
			v = ch[v][1];
		} else {
			break;
		}
		if(i == 29) {
			if(val[v] >= 0) {
				ans = std::max(ans, val[v] + 1);
			}
		}
	}
	return ans;
}
std::map<int, int> M;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		scanf("%d%d%d", &N, &X, &L);
		scanf("%d%d%d", &A[1], &P, &Q);
		for(int i = 0; i < 30; i++) {
			bx[i] = (X & 1);
			X >>= 1;
		}
		std::reverse(bx, bx + 30);
		suf[1] = A[1];
		for(int i = 2; i <= N; i++) {
			A[i] = (A[i - 1] * (long long) P + Q) % MOD;
			suf[i] = suf[i - 1] ^ A[i];
		}
		std::memset(ch[0], 0, sizeof ch[0]);
		M.clear();
		val[0] = -1;
		sz = 0;
		insert(0, 0);
		M[0] = 0;
		for(int i = 1; i <= N; i++) {
			if(i - L - 1 >= 0 && M[suf[i - L - 1]] == i - L - 1) {
				del(suf[i - L - 1]);
			}
			int res = query(suf[i]);
			dp[i] = res;
			if(res > 0) {
				insert(suf[i], res);
				M[suf[i]] = i;
			}
		}
		printf("%d\n", dp[N]);
	}
	return 0;
}
