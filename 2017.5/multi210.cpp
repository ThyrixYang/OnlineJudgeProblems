#include <bits/stdc++.h>

int a, v1, v2;
double x, y;
int main() {
	while(scanf("%d%d%d", &a, &v1, &v2) != EOF) {
		if(v1 <= v2) {
			puts("Infinity");
			continue;
		}
		double ans = 0;
		x = 0, y = a;
		double dt = 1e-5;
		for(int i = 0; i < 1e5; i++) {
			double dx = -x / sqrt(x * x + y * y) * v1 + v2;
			double dy = -y / sqrt(x * x + y * y) * v1;
			x += dx * dt, y += dy *dt;
			printf("%.2f %.2f\n", x, y);
			if(std::fabs(x / dx) < 1e-6) break;
			ans += dt;
		}
		printf("%.5f\n", ans);
	}
	return 0;
}
