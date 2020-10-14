#include <bits/stdc++.h>

const int MAXN = 1e6;
int N, K, X;
long long a[MAXN];
long long sgn(long long x) {
	if(x > 0) return 1;
	if(x == 0) return 0;
	else return -1;
}
struct Node {
	long long pos, val;
	bool operator < (const Node &C) const {
		return std::abs(val) > std::abs(C.val);
	}
	Node(long long pos, long long val) :pos(pos), val(val){}
};
int main() {
	freopen("in", "r", stdin);
	std::cin >> N >> K >> X;
	long long c0 = 0, c1 = 0, c2 = 0;
	for(int i = 0; i < N; i++) {
		scanf("%lld", &a[i]);
		if(a[i] > 0) c1++;
		else if(a[i] < 0) c2++;
		else c0++;
	}
	if(c0 > K) {
		for(int i = 0; i < N; i++) printf("%lld ", a[i]);
		puts("");
		return 0;
	}
	if(c2 % 2 == 1) {
		for(int i = 0; i < N; i++) {
			if(a[i] == 0) a[i] = X, K--;
		}
	} else {
		for(int i = 0; i < N; i++) {
			if(a[i] == 0) {
				a[i] = -X, K--;
				c2++;
				break;
			}
		}
		for(int i = 0; i < N; i++) {
			if(a[i] == 0) {
				a[i] = X, K--;
			}
		}
	}
	if(c2 % 2 == 0) {
		long long minval = 1e18;
		for(int i = 0; i < N; i++) {
			if(std::abs(a[i]) < std::abs(minval)) {
				minval = a[i];
			}
		}
		if((long long)X * K <= std::abs(minval)) {
			for(int i = 0; i < N; i++) {
				if(a[i] == minval) {
					a[i] -= sgn(a[i]) * (long long)X * K;
					break;
				}
			}
			for(int i = 0; i < N; i++) {
				printf("%lld ", a[i]);
			}
			puts("");
			return 0;
		} else {
			for(int i = 0; i < N; i++) {
				if(a[i] == minval) {
					long long s = sgn(a[i]);
					while(sgn(a[i] - s * X) * s >= 0) {
						a[i] -= s * X;
						K--;
					}
					if(a[i] * s >= 0) a[i] -= s * X, K--;
					break;
				}
			}
		}
	}
	std::priority_queue<Node> Q;
	for(int i = 0; i < N; i++) {
		Q.push(Node(i, a[i]));
	}
	while(K > 0) {
		Node tmp = Q.top();
		Q.pop();
		tmp.val += sgn(tmp.val) * X;
		a[tmp.pos] = tmp.val;
		K--;
		Q.push(tmp);
	}
	for(int i = 0; i < N; i++) printf("%lld ", a[i]);
	return 0;
}
