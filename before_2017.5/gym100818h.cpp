#include <bits/stdc++.h>

const int MAXK = 1005;
const int MAXN = 1e4 + 20;
int K, N, T;
bool used[MAXK][MAXN];
int fa[MAXN], cnt[MAXN];
int last[MAXN];
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> K >> N;
	std::cin >> T;
	for(int i = 0; i < MAXN; i++) fa[i] = i, cnt[i] = 1;
	long long res1 = 0;
	for(int i = 0; i < T; i++) {
		int pl, st, fn;
		scanf("%d%d%d", &pl, &st, &fn);
		for(int j = st; j < fn; j++) {
			used[pl][j] = 1;
		}
	}
	for(int i = 1; i <= K; i++) {
		for(int j = 1; j <= N - 1; j++) {
			if(!used[i][j]) {
				if(find(j) == find(j + 1)) continue;
				long long c1 = cnt[find(j)];
				long long c2 = cnt[find(j + 1)];
				res1 -= c1 * (c1 - 1);
				res1 -= c2 * (c2 - 1);
				res1 += (c1 + c2) * (c1 + c2 - 1);
				fa[find(j)] = find(j + 1);
				cnt[find(j + 1)] += c1;
			}
		}
	}
	for(int i = 1; i <= K; i++) {
		for(int j = 1; j < N; j++) {
			if(!used[i][j]) {
				int k = j;
				while(k < N && !used[i][k]) k++;
				last[j] = std::max(last[j], k);
				j = k;
			}
		}
	}
	for(int i = 2; i <= N; i++) {
		last[i] = std::max(last[i], last[i - 1]);
	}
	for(int i = 1; i <= N; i++) {
		if(last[i] >= i) {
			res1 -= (last[i] - i) * 2;
		}
	}
	res1 /= 2;
	printf("%lld\n", res1);
	return 0;
}
