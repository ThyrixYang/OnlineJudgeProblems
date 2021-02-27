#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1);
const double EPS = 1e-8;
int T;
int main() {
	freopen("../Data/stdin", "r", stdin);
	freopen("../Data/stdout", "w", stdout);
	cin >> T;
	for(int cas = 1; cas <= T; cas++) {
		int P, X, Y;
		scanf("%d%d%d", &P, &X, &Y);
		X -= 50;
		Y -= 50;
		printf("Case #%d: ", cas);
		if(X == 0 && Y == 0) {
			if(P == 0) puts("white");
			else puts("black");
			continue;
		}
		double ang = P * PI * 2 / 100;
		double a2 = atan2((double)-Y, (double)-X) + PI;
		//printf("%.3f %.3f\n", ang, a2);
		if(a2 < ang + EPS && X * X + Y * Y <= 50 * 50) puts("black");
		else puts("white");
	}
	return 0;
}
