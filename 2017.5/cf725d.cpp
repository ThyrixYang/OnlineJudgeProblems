#include <bits/stdc++.h>

const int MAXN = 1e6;
int N;
struct Node {
	long long t, w;
	bool operator < (const Node& A) const {
		if(t != A.t) return t > A.t;
		return w - t < A.w - A.t;
	}
}a[MAXN];
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N;
	for(int i = 0; i < N; i++) { 
		scanf("%lld%lld", &a[i].t, &a[i].w);
	}
	std::sort(a + 1, a + N);
	std::priority_queue<long long> Q1;
	std::priority_queue<long long, std::vector<long long>, 
		std::greater<long long> > Q2;
	int p = 1;
	while(p < N && a[p].t > a[0].t) {
		Q2.push(a[p].w - a[p].t + 1);
		p++;
	}
	int ans = p;
	long long sum = 0;
	for(int i = p; i < N; i++) {
		int j = i;
		while(a[i].t == a[i + 1].t && i + 1 < N) i++;
		while(p < N && a[p].t > a[i].t) {
			Q2.push(a[p].w - a[p].t + 1);
			p++;
		}
		int f = 1;
		for(;f;) {
			f = 0;
			if(!Q1.empty() && !Q2.empty()) {
				long long x1 = Q1.top();
				long long x2 = Q2.top();
				if(x2 < x1) {
					f = 1;
					sum += x2 - x1;
					Q1.pop();
					Q2.pop();
					Q1.push(x2);
					Q2.push(x1);
				}
			}
			if(!Q2.empty() && sum + Q2.top() <= a[0].t - a[i].t) {
				f = 1;
				sum += Q2.top();
				Q1.push(Q2.top());
				Q2.pop();
			}
		}
		ans = std::min(ans, int(j - Q1.size()));
	}
	while(p < N) {
		Q2.push(a[p].w - a[p].t + 1);
		p++;
	}
	int f = 1;
	for(;f;) {
		f = 0;
		if(!Q1.empty() && !Q2.empty()) {
			long long x1 = Q1.top();
			long long x2 = Q2.top();
			if(x2 < x1) {
				f = 1;
				sum += x2 - x1;
				Q1.pop();
				Q2.pop();
				Q1.push(x2);
				Q2.push(x1);
			}
		}
		if(!Q2.empty() && sum + Q2.top() <= a[0].t) {
			f = 1;
			sum += Q2.top();
			Q1.push(Q2.top());
			Q2.pop();
		}
	}
	ans = std::min(ans, int(N - Q1.size()));
	std::cout << ans << std::endl;
	return 0;
}
