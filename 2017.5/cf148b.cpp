#include <bits/stdc++.h>

const double EPS = 1e-8;
int vp, vd, t, f, c;
int sgn(double x) {
	if(std::fabs(x) < EPS) return 0;
	if(x > 0) return 1;
	return -1;
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> vp >> vd >> t >> f >> c;
	double pos = vp * t;
	int ans = 0;
	if(sgn(pos - c) >= 0 || vp >= vd) {
		puts("0");
		return 0;
	}
	for(;;) {
		double t1 = pos / (vd - vp);
		pos += t1 * vp;
		if(sgn(pos - c) >= 0) break;
		ans++;
		pos += (pos / vd + f) * vp;
	}
	printf("%d\n", ans);
	return 0;
}
