#include <bits/stdc++.h>

const int MAXN = 2e5 + 300;
struct Node {
	int x, p;
	bool operator < (const Node & A) const {
		return x < A.x;
	}
}a[MAXN], b[MAXN];
int N;
int c[MAXN];
int main() {
	freopen("in.txt", "r", stdin);
	std::cin >> N;
	for(int i = 0; i < N; i++) {
		scanf("%d", &a[i].x);
		a[i].p = i;
	}
	for(int i = 0; i < N; i++) {
		scanf("%d", &b[i].x);
		b[i].p = i;
	}
	std::sort(a, a + N);
	std::sort(b, b + N);
	int cnt = 0;
	for(int s = N * 2 - 2; cnt < N; s--) {
		for(int i = std::max(0, s - (N - 1)); i <= N - 1 && cnt < N; i++) {
			int j = s - i;
			if(j < 0) break;
			int p = (a[i].p + b[j].p) % N;
			if(c[p] == 0) {
				c[p] = a[i].x + b[j].x;
				cnt++;
			}
		}
	}
	for(int i = 0; i < N; i++) {
		printf("%d", c[i]);
		if(i < N - 1) printf(" ");
	}
	return 0;
}
