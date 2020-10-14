#include <bits/stdc++.h>

const int MAXN = 2005;
int N, M, K;
double p[4];
double dp[2][MAXN];
double pp[MAXN];
const double EPS = 1e-5;
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d%d%d", &N, &M, &K) != EOF) {
		for(int i = 0; i < 4; i++) scanf("%lf", &p[i]);
		if(p[3] < EPS) {
			puts("0.00000");
			continue;
		}
		for(int i = 1; i < 4; i++) {
			p[i] /= (1 - p[0]);
		}
		pp[0] = 1;
		for(int i = 1; i <= N; i++) pp[i] = pp[i - 1] * p[1];
		dp[1][1] = p[3] / (p[2] + p[3]);
		for(int i = 2; i <= N; i++) {
			int f = (i & 1);
			int g = (f ^ 1);
			for(int j = 1; j <= i; j++) {
				if(j == 1) dp[f][j] = p[3];
				else if(j <= K) {
					dp[f][j] = dp[g][j - 1] * p[2] + dp[f][j - 1] * p[1] + p[3];
				} else {
					dp[f][j] = dp[g][j - 1] * p[2] + dp[f][j - 1] * p[1];
				}
			}
			dp[f][i] /= (1 - pp[i]);
			for(int j = 1; j < i; j++) {
				dp[f][j] += pp[j] * dp[f][i];
			}
		}
		printf("%.5f\n", dp[N & 1][M]);
	}
	return 0;
}
