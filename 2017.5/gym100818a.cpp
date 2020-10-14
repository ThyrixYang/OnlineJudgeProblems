#include <bits/stdc++.h>

const int MAXN = 1e5;
const int MAXM = 1e6;
int stk[MAXM], top;
char tmp[MAXN], A[MAXN], B[MAXN];
int lena, lenb;
int matcha[MAXN], matchb[MAXN];
int val[MAXN];
int fuc(char *s) {
	int len = 0;
	int n = strlen(s);
	for(int i = 0; i < n; i++) {
		if(s[i] != ' ') s[len++] = s[i];
	}
	s[len] = 0;
	return len;
}
int cala(int l, int r) {
	if(r - l == 1) return val[(int)A[l]];
	if(A[l] == '(') {
		int t = matcha[l];
		int res = cala(l + 1, t);
		if(t + 1 >= r) return res;
		if(A[t + 1] == 'V') return (res) || (cala(t + 2, r));
		else return (res) && (cala(t + 2, r));
	}else if(A[l] == '~') {
		int f = 0;
		while(A[l] == '~') l++, f ^= 1;
		l--;
		if(A[l + 1] == '(') {
			int t = matcha[l + 1];
			int res = cala(l + 2, t);
			res ^= f;
			if(t + 1 >= r) return res;
			if(A[t + 1] == 'V') return (res) || (cala(t + 2, r));
			else return (res) && (cala(t + 2, r));
		} else {
			int res = cala(l + 1, l + 2);
			res ^= f;
			if(l + 2 == r) return res;
			if(A[l + 2] == 'V') return (res) || (cala(l + 3, r));
			else return (res) && (cala(l + 3, r));
		}
	} else {
		int res = cala(l, l + 1);
		if(A[l + 1] == 'V') return res || cala(l + 2, r);
		else return res && cala(l + 2, r);
	}
}
int calb(int l, int r) {
	if(r - l == 1) return val[(int)B[l]];
	if(B[l] == '(') {
		int t = matchb[l];
		int res = calb(l + 1, t);
		if(t + 1 >= r) return res;
		if(B[t + 1] == 'V') return (res) || (calb(t + 2, r));
		else return (res) && (calb(t + 2, r));
	}else if(B[l] == '~') {
		int f = 0;
		while(B[l] == '~') l++, f ^= 1;
		l--;
		if(B[l + 1] == '(') {
			int t = matchb[l + 1];
			int res = calb(l + 2, t);
			res ^= f;
			if(t + 1 >= r) return res;
			if(B[t + 1] == 'V') return (res) || (calb(t + 2, r));
			else return (res) && (calb(t + 2, r));
		} else {
			int res = calb(l + 1, l + 2);
			res ^= f;
			if(l + 2 == r) return res;
			if(B[l + 2] == 'V') return (res) || (calb(l + 3, r));
			else return (res) && (calb(l + 3, r));
		}
	} else {
		int res = calb(l, l + 1);
		if(B[l + 1] == 'V') return res || calb(l + 2, r);
		else return res && calb(l + 2, r);
	}
}
int main() {
	freopen("./in", "r", stdin);
	srand(2344);
	gets(A);
	gets(B);
	lena = fuc(A);
	lenb = fuc(B);
	top = 0;
	for(int i = 0; i < lena; i++) {
		if(A[i] == '(') stk[top++] = i;
		else if(A[i] == ')') matcha[stk[--top]] = i;
	}
	top = 0;
	for(int i = 0; i < lenb; i++) {
		if(B[i] == '(') stk[top++] = i;
		else if(B[i] == ')') matchb[stk[--top]] = i;
	}
	int f = 1;
	for(int rep = 0; rep < 6000; rep++) {
		for(int i = 0; i < 26; i++) {
			val['a' + i] = rand() % 2;
			val['A' + i] = rand() % 2;
		}
		if(cala(0, lena) != calb(0, lenb)) {
			f = 0;
			break;
		}
	}
	printf("%d\n", f);
	return 0;
}
