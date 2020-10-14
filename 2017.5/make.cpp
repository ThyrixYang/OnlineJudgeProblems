#include <bits/stdc++.h>

const int MAXN = 500;
double R() {
	return (rand() % 10000 * 1.0 / 10 - 500);
}
int main() {
	freopen("./in", "w", stdout);
	srand(time(0));
	for(int i = 0; i < MAXN; i++) {
		double x = i;
		double y = 2.3334 * x + 22;
		printf("%.8f,%.8f\n", x, y);
	}
	return 0;
}
