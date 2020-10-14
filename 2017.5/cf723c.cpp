#include <bits/stdc++.h>

typedef std::pair<int, int> P;
const int MAXN = 3000;
int N, M;
int a[MAXN];
int b[MAXN];
std::vector<int> pos[MAXN];
int cnt[MAXN];
int iter[MAXN];
int check(int k) {
	std::memset(cnt, 0, sizeof cnt);
	std::memset(iter, 0, sizeof iter);
	for(int i = 0; i < N; i++) {
		if(a[i] <= M) cnt[a[i]]++;
		else cnt[M + 1]++;
		b[i] = a[i];
	}
	std::priority_queue<P> Q;
	for(int i = 1; i <= M; i++) {
		if(cnt[i] > k) Q.push(P(cnt[i], i));
	}
	for(int i = 1; i <= M; i++) {
		while(cnt[i] < k) {
			int nt = -1;
			if(cnt[M + 1] > 0) {
				nt = pos[M + 1][iter[M + 1]++];
				cnt[M + 1]--;
			}
			if(nt == -1) {
				if(Q.empty()) return 0;
				int p = Q.top().second;
				Q.pop();
				nt = pos[p][iter[p]++];
				cnt[p]--;
				if(cnt[p] > k) {
					Q.push(P(cnt[p], p));
				}
			}
			if(nt == -1) return 0;
			b[nt] = i;
			cnt[i] ++;
		}
	}
	return 1;
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N >> M;
	for(int i = 0; i < N; i++) {
		scanf("%d", &a[i]);
		if(a[i] <= M) pos[a[i]].push_back(i);
		else pos[M + 1].push_back(i);
	}
	int l = 0, r = N + 1;
	while(r - l > 1) {
		int mid = (r + l) >> 1;
		if(check(mid)) l = mid;
		else r = mid;
	}
	check(l);
	int mm = 1e9;
	for(int i = 1; i <= M; i++) mm = std::min(mm, cnt[i]);
	int chg = 0;
	for(int i = 0; i < N; i++) {
		chg += a[i] != b[i];
	}
	printf("%d %d\n", mm, chg);
	for(int i = 0; i < N; i++) printf("%d ", b[i]);
	return 0;
}
