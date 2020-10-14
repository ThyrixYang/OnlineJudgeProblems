#include <bits/stdc++.h>

const long long MOD = 1e9 + 7;
void ma(int &a, int b) {
	a += b;
	if(a >= MOD) a -= MOD;
	if(a < 0) a += MOD;
}
void FMT(std::vector<int>& f, int n, int on) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < (1 << n); j++) {
			if(j & (1 << i)) continue;
			ma(f[j | (1 << i)], on * f[j]);
		}
	}
}
char s[1000];
int N;
int se[20][2];
int match[1000];
int stk[1000], top;
std::vector<int> pre[4][2], prex;
void preCal() {
	for(int i = 0; i < 4; i++) {
		pre[i][0] = pre[i][1] = std::vector<int> (1 << 16);
	}
	prex = std::vector<int> (1 << 16);
	for(int i = 0; i < 4; i++) {
		for(int v = 0; v < 2; v++) {
			for(int j = 0; j < (1 << 16); j++) {
				int f = 1;
				for(int k = 0; k < 16; k++) {
					if((((k >> i) & 1) ^ v ^ ((j >> k) & 1)) != 0) {
						f = 0;
						break;
					}
				}
				pre[i][v][j] += f;
				prex[j] += f;
			}
		}
	}
}
void exchange(std::vector<int>& a) {
	int X = (1 << 16) - 1;
	for(int i = 0; i < (1 << 16); i++) {
		int j = (i ^ X);
		if(j > i) std::swap(a[i], a[j]);
	}
}
std::vector<int> combineAnd(std::vector<int> &a, std::vector<int> b) {
	exchange(a);exchange(b);
	FMT(a, 16, 1);FMT(b, 16, 1);
	for(int i = 0; i < (1 << 16); i++) {
		a[i] = a[i] * (long long)b[i] % MOD;
	}
	FMT(a, 16, -1);
	exchange(a);
	return a;
}
std::vector<int> combineOr(std::vector<int> &a, std::vector<int> b) {
	FMT(a, 16, 1);FMT(b, 16, 1);
	for(int i = 0; i < (1 << 16); i++) {
		a[i] = a[i] * (long long)b[i] % MOD;
	}
	FMT(a, 16, -1);
	return a;
}
std::vector<int> DP(int l, int r) {
	if(r - l == 1) {
		if(s[l] == '?') {
			return prex;
		} else {
			if(isupper(s[l])) {
				return pre[s[l] - 'A'][0];
			} else {
				return pre[s[l] - 'a'][1];
			}
		}
	}
	if(s[l] == '(' && match[l] == r - 1) {
		return DP(l + 1, r - 1);
	}
	std::vector<int> fr, bk;
	int p;
	if(s[l] == '(') {
		fr = DP(l + 1, match[l]);
		p = match[l] + 1;
	} else {
		fr = DP(l, l + 1);
		p = l + 1;
	}
	bk = DP(p + 1, r);
	if(s[p] == '?') {
		std::vector<int> tmp = fr;
		combineAnd(fr, bk);
		combineOr(tmp, bk);
		for(int i = 0; i < (1 << 16); i++) {
			ma(fr[i], tmp[i]);
		}
	} else {
		if(s[p] == '&') combineAnd(fr, bk);
		else combineOr(fr, bk);
	}
	return fr;
}
int main() {
	freopen("in.txt", "r", stdin);
	preCal();
	scanf("%s", s);
	std::cin >> N;
	for(int i = 0; i < N; i++) {
		int y;
		for(int j = 0; j < 4; j++) {
			scanf("%d", &y);
			se[i][0] += (y << j);
		}
		scanf("%d", &se[i][1]);
	}
	int len = strlen(s);
	for(int i = 0; i < len; i++) {
		if(s[i] == '(') {
			stk[top++] = i;
		} else if(s[i] == ')') {
			top--;
			match[stk[top]] = i;
		}
	}
	std::vector<int> res = DP(0, len);
	int ans = 0;
	for(int i = 0; i < (1 << 16); i++) {
		int f = 1;
		for(int j = 0; j < N; j++) {
			if(((i >> se[j][0]) & 1) != se[j][1]) {
				f = 0;
				break;
			}
		}
		ma(ans, f * res[i]);
	}
	std::cout << ans << std::endl;
	return 0;
}
