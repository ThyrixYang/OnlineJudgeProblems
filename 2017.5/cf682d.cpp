#include <bits/stdc++.h>

using namespace std;
const int maxn = 1005;
char s[maxn], t[maxn];
int ls, lt, k;
int dp[maxn][maxn][12][2];
#define ma(a, b) a = max(a, b);
int main() {
	freopen("./in", "r", stdin );
	cin >> ls >> lt >> k;
	scanf("%s%s", s, t);
	int ans = 0;
	for (int i = 0; i <= ls; i++) {
		for (int j = 0; j <= lt; j++) {
			for(int x = 0; x <= k; x++) {
				ma(dp[i + 1][j + 1][x][0], max(dp[i + 1][j][x][0], dp[i][j + 1][x][0]));
				if(s[i] == t[j]) {
					if(dp[i][j][x][1]) ma(dp[i + 1][j + 1][x][1], dp[i][j][x][1] + 1);
					ma(dp[i + 1][j + 1][x + 1][1], dp[i][j][x][0] + 1);
				}
				ma(dp[i + 1][j + 1][x][0],dp[i + 1][j + 1][x][1]);
			}
		}
	}
	cout << dp[ls][lt][k][0] << endl;
	return 0;
}
