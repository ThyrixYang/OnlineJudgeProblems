#include <bits/stdc++.h>

using namespace std;
const int MAXN = 1000;
int N, M;
long long a[MAXN];
long long res[MAXN];
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N >> M;
	for(int i = 1; i <= N; i++) {
		scanf("%lld", &a[i]);
	}
	for(int i = 0; i <= N; i++) {
		long long l = -1e18, r = 1e18;
		while(r - l > 1) {
			long long mid = (r + l) / 2;
			int cnt = 0;
			long long w = mid;
			priority_queue<int, vector<int>, greater<int> > Q;
			for(int j = 1; j <= N; j++) {
				w += a[j];
				Q.push(a[j]);
				if(w < 0) {
					w -= Q.top();
					Q.pop();
					cnt++;
				}
			}
			if(cnt <= i) r = mid;
			else l = mid;
		}
		res[i] = r;
	}
	while(M--) {
		long long w;
		scanf("%lld", &w);
		int l = -1, r = N;
		while(r - l > 1) {
			int mid = (r + l) >> 1;
			if(res[mid] <= w) r = mid;
			else l = mid;
		}
		printf("%d\n", r);
	}
	return 0;
}
