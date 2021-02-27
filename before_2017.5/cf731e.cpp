#include <bits/stdc++.h>

using namespace std;
const int MAXN = 1e6;
int N;
int a[MAXN], sum[MAXN];
int dp[MAXN];
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N;
	for(int i = 1; i <= N; i++) {
		scanf("%d", &a[i]);
		sum[i] = sum[i - 1] + a[i];
	}
	priority_queue<int> Q;
	dp[N] = sum[N];
	Q.push(sum[N - 1] - dp[N]);
	Q.push(sum[N]);
	for(int i = N - 1; i >= 1; i--) {
		dp[i] = Q.top();
		Q.push(sum[i - 1] - dp[i]);
	}
	for(int i = 2; i <= N; i++) {
		//printf("%d ", dp[i]);
	}
	std::cout << dp[2] << std::endl;		
	return 0;
}
