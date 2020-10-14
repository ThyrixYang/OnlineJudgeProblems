#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000;
int T;
int N;
int w[MAXN];
int main() {
	freopen("../Data/stdin", "r", stdin);
	freopen("../Data/stdout", "w", stdout);
	cin >> T;
	for(int cas = 1; cas <= T; cas++) {
		cin >> N;
		for(int i = 0; i < N; i++) {
			scanf("%d", &w[i]);
		}
		sort(w, w + N, greater<int>() );
		int ans = 0;
		int need = 0;
		for(int i = 0; i < N; i++) {
			need += (50 + w[i] - 1) / w[i];
			if(need <= N) {
				ans = i + 1;
			}
			else {
				break;
			}
		}
		printf("Case #%d: %d\n", cas, ans);
	}
	return 0;
}
