#include <bits/stdc++.h>

using namespace std;
const int MAXN = 1024;
int N;
int A[MAXN];
int sq[8];
int dp[MAXN][8];
int cnt[10][MAXN];
int ans = 0;
int Cal() {
	
}
int main() {
	//freopen("in.txt", "r", stdin);
	cin >> N;
	for(int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
		cnt[A[i]][i] = 1;
	}
	for(int i = 1; i <= 8; i++) {
		for(int j = 1; j <= N; j++) {
			cnt[i][j] += cnt[i][j - 1];
		}
	}
	for(int i = 0; i < 8; i++) {
		sq[i] = i + 1;
	}
	do {
		

	} while(next_permutation(sq, sq + 8));
	cout << ans << endl;
	return 0;
}
