#include <bits/stdc++.h>

struct Node {
	int x, y;
	Node(int x = 0, int y = 0): x(x), y(y) {}
	void in(){scanf("%d%d", &x, &y);}
};
const int MAXN = 1e5 + 3000;
int n, m;
Node pn[MAXN], pm[MAXN];
bool cmp(const Node &a, const Node &b) {
	if(a.y != b.y) return a.y < b.y;
	return a.x > b.x;
}
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d%d\n", &n, &m) != EOF) {
		for(int i = 0; i < n; i++) pn[i].in();
		for(int i = 0; i < m; i++) pm[i].in();
		std::sort(pn, pn + n, cmp);
		std::sort(pm, pm + m, cmp);
		std::map<int, int> M;
		int cnt = 0;
		long long ans = 0;
		for(int i = 0, j = 0; i < n; i++) {
			while(j < m && pm[j].y <= pn[i].y) {
				++M[pm[j].x * 500 + pm[j].y * 2];
				j++;
			}
			int k = pn[i].x * 500 + pn[i].y * 2;
			std::map<int, int>::iterator it = M.lower_bound(k);
			if(M.empty()) continue;
			if(it == M.end()) it--;
			if(it->first > k && it == M.begin()) continue;
			if(it->first > k) it--;
			cnt++;
			ans += it->first;
			if(--it->second == 0) M.erase(it);
		}
		printf("%d %lld\n", cnt, ans);
	}
	return 0;
}
