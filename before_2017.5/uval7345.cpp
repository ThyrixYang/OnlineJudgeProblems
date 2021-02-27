#include <bits/stdc++.h>

const double PI = acos(-1);
const double EPS = 5e-8;
int T, n;
double a;
double theta[20];
double cal(double a, double t1, double t2) {
	return a * a * (t2 * t2 * t2 - t1 * t1 * t1) / 6;
}
typedef std::pair<int, int> P;
int cas = 0;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		std::set<P> S;
		scanf("%lf", &a);
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%lf", &theta[i]);
		std::sort(theta, theta + n);
		int q;
		scanf("%d", &q);
		printf("Spiral %d:", ++cas);
		double ans = 0;
		while(q--) {
			double r, t;
			scanf("%lf%lf", &r, &t);
			if(n == 0) {
				continue;
			}
			int pos = std::lower_bound(theta, theta + n, t) - theta;
			int loop = (r + PI * 2 * a -  t * a) / PI / 2 / a + EPS;
			double t1, t2;
			int s1, s2;
			if(pos == 0) {
				t1 = theta[n - 1] + (loop - 1) * PI * 2;
				t2 = theta[0] + loop * PI * 2;
				s1 = 0, s2 = loop - 1;
			} else if(pos == n) {
				t1 = theta[n - 1] + loop * PI * 2;
				t2 = theta[0] + 2 * PI * (loop + 1);
				s1 = 0, s2 = loop;
			} else {
				t1 = theta[pos - 1] + (loop - 1) * PI * 2;
				t2 = theta[pos] + (loop - 1) * PI * 2;
				s1 = pos - 1, s2 = loop - 1;
			}
			if(S.find(P(s1, s2)) != S.end()) continue;
			S.insert(P(s1, s2));
			ans += -cal(a, t1, t2) + cal(a, t1 + 2 * PI, t2 + 2 * PI);
		}
		if(n != 0) printf(" %.4f liters\n", ans / 10);
		else puts(" -1");
	}
	return 0;
}

