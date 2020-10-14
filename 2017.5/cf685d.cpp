#include <bits/stdc++.h>

const int maxn = 100005 * 302;
int n, k;
struct Event {
	int x, y;
	int f;
	Event(int x = 0, int y = 0, int f = 0): x(x), y(y), f(f) {}
	bool operator < (const Event &C) const {
		return x < C.x;
	}
}events[100005 * 2];
long long ans[100005];
std::vector<int> pos;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> n >> k;
	for(int i = 0; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		for(int j = 0; j < k; j++)
			pos.push_back(y - j);
		events[i] = Event(x, y, 1);
		events[i + n] = Event(x + k, y, -1);
	}
	std::sort(events, events + n * 2);
	std::sort(pos.begin(), pos.end());
	pos.erase(std::unique(pos.begin(), pos.end()), pos.end());
	for(int i = 0; i < n * 2; i++) events[i].y = lower_bound(pos.begin(), pos.end(), 
			events[i].y) - pos.begin();
	for(int i = 0; i < pos.size(); i++) pos[i] = 0;
	std::vector<int> &cnt = pos;
	std::vector<int> last(pos.size(), 0);
	for(int i = 0; i < n * 2; i++) {
		int a = events[i].x, b = events[i].y, f = events[i].f;
		for(int j = 0; j < k; j++) {
			int p = b - j;
			ans[cnt[p]] += a - last[p];
			cnt[p] += f;
			last[p] = a;
		}
	}
	for(int i = 1; i <= n; i++)
		printf("%lld\n", ans[i]);
	return 0;
}
