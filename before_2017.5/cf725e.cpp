#include <bits/stdc++.h>

const int MAXN = 1e6;
int C, N;
int a[MAXN];
int dic[MAXN], dh;
int cnt[MAXN];
int find(int x, int p) {
	int l = -1, r = p + 1;
	while(r - l > 1) {
		int mid = (r + l) >> 1;
		if(dic[mid] > x) r = mid;
		else l = mid;
	}
	return l;
}
bool check(int c, int p) {
	if(c == 0) return 1;
	for(;;) {
		int id = find(c, p);
		if(id == -1) return 0;
		int need = c / dic[id];
		need = std::min(need, cnt[id]);
		c -= need * dic[id];
		if(c == 0) return 1;
		p = std::min(p - 1, id - 1);
	}
	return 0;
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> C >> N;
	for(int i = 0; i < N; i++) {
		scanf("%d", &a[i]);
		dic[i] = a[i];
	}
	std::sort(dic, dic + N);
	dh = std::unique(dic, dic + N) - dic;
	for(int i = 0; i < N; i++) {
		int id = std::lower_bound(dic, dic + dh, a[i]) - dic;
		++cnt[id];
	}
	int ans = -1;
	int sum = 0;
	int p = dh - 1;
	for(int val = C - 1; val > 0; val--) {
		while(p >= 0 && dic[p] > val) {
			int n = (C - sum) / dic[p];
			n = std::min(cnt[p], n);
			sum += n * dic[p];
			p--;
		}
		if(sum == C) break;
		if(C - sum - val > 0 && !check(C - sum - val, p)) ans = val;
	}
	if(ans == -1) {
		puts("Greed is good");
	} else {
		std::cout << ans << std::endl;
	}
	return 0;
}
