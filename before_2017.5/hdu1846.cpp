#include <bits/stdc++.h>

const int MAXN = 1005;
int T;
int N, M;
int a[MAXN];
int main() {
	freopen("in", "r", stdin);
	std::cin >> T;
	while(T--) {
		std::cin >> N >> M;
		for(int i = 1; i <= N; i++) {
			int f = 0;
			for(int j = 1; j <= M; j++) {
				if(i - j < 0) break;
				if(a[i - j] == 0) {
					f = 1;
					break;
				}
			}
			a[i] = f;
		}
		if(a[N]) puts("first");
		else puts("second");
	}
	return 0;
}