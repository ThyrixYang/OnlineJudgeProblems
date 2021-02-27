#include <bits/stdc++.h>

const int MAXN = 1e5 + 300;
int val[MAXN];
int idx[MAXN];
int a[MAXN], ah;
int b[MAXN], bh;
int n;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> n;
	for(int i = 1; i <= n; i++) scanf("%d", &val[i]), idx[i] = i;
	std::sort(idx + 1, idx + n + 1, [](int a, int b){return val[a] < val[b];});
	int l = n / 2, r = l + 1;
	int s1 = 0, s2 = 0;
	for(;;) {
		if(l <= 0) break;
		if(s1 < s2) {
			a[ah++] = idx[r];
			b[bh++] = idx[l];
			s1 += val[idx[r]];
			s2 += val[idx[l]];
		} else {
			a[ah++] = idx[l];
			b[bh++] = idx[r];
			s1 += val[idx[l]];
			s2 += val[idx[r]];
		}
		l--, r++;
	}
	if(n % 2 == 1) {
		if(s1 < s2) a[ah++] = idx[n];
		else b[bh++] = idx[n];
	}
	printf("%d\n", ah);
	for(int i = 0; i < ah; i++) {
		printf("%d ", a[i]);
	}
	puts("");
	printf("%d\n", bh);
	for(int i = 0; i < bh; i++) {
		printf("%d ", b[i]);
	}
	puts("");
	return 0;
}
