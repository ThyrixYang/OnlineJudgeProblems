#include <bits/stdc++.h>

typedef unsigned int ui;
int T, N;
char mat[20][20];
ui dp[1 << 20];
ui tmp[1 << 20];
int cnt[1 << 20];
int a[20], ah;
void FMT(ui *f, int n, int on) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < (1 << n); j++) {
			if(j & (1 << i)) continue;
			if(on == 1) f[j | (1 << i)] += f[j];
			else f[j | (1 << i)] -= f[j];
		}
	}
}
int main() {
	freopen("in.txt", "r", stdin);
	std::cin >> T;
	while(T--) {
		scanf("%d", &N);
		for(int i = 0; i < N; i++) {
			scanf("%s", mat[i]);
			for(int j = 0; j < N; j++) {
				mat[i][j] -= '0';
			}
		}
		std::memset(cnt, 0x3f, sizeof(int) * (1 << N));
		for(int i = 0; i < (1 << N); i++) {
			ah = 0;
			for(int j = 0; j < N; j++) {
				if(i & (1 << j))  a[ah++] = j;
			}
			int f = 1;
			for(int j = 0; j < ah && f == 1; j++) {
				for(int k = j + 1; k < ah && f == 1; k++) {
					if(mat[a[j]][a[k]]) {
						f = 0;
					}
				}
			}
			if(f) cnt[i] = 1;
			dp[i] = f;
		}
		std::memcpy(tmp, dp, sizeof (ui) * (1 << N));
		FMT(tmp, N, 1);
		for(int i = 0; i < N; i++) {
			FMT(dp, N, 1);
			for(int j = 0; j < (1 << N); j++) {
				dp[j] *= tmp[j];
			}
			FMT(dp, N, -1);
			for(int j = 0; j < (1 << N); j++) {
				dp[j] = (dp[j] != 0);
			}
			int cc = 0;
			for(int j = 0; j < (1 << N); j++) {
				if(dp[j] != 0 && cnt[j] > N) cnt[j] = i + 2;
				if(cnt[j] <= N) cc++;
			}
			if(cc == N) break;
		}
		ui ans = 0;
		for(int i = (1 << N) - 1; i >= 1; i--) {
			ans += cnt[i];
			ans *= 233;
		}
		std::cout << ans << std::endl;
	}
	return 0;
}
