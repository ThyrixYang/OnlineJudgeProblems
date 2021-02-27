#include <bits/stdc++.h>

const int maxn = 1e6;
int a[maxn], b[maxn];
int n;
int sta[20][maxn], stb[20][maxn];
void ST() {
	for(int i = 1; i <= n; i++) sta[0][i] = a[i], stb[0][i] = b[i];
	for(int k = 1; k < 20; k++) {
		for(int i = 1; i <= n; i++) {
			if(i + (1 << (k - 1)) >= maxn) break;
			sta[k][i] = std::max(sta[k - 1][i], sta[k - 1][i + (1 << (k - 1))]);
			stb[k][i] = std::min(stb[k - 1][i], stb[k - 1][i + (1 << (k - 1))]);
		}
	}
}
int geta(int l, int r) {
	int d = r - l;
	int k = 0;
	while(1 << (k + 1) <= d) k++;
	return std::max(sta[k][l], sta[k][r - (1 << k)]);
}
int getb(int l, int r) {
	int d = r - l;
	int k = 0;
	while(1 << (k + 1) <= d) k++;
	return std::min(stb[k][l], stb[k][r - (1 << k)]);
}
int main() {
	std::cin >> n;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	ST();
	long long ans = 0;
	for(int i = 1; i <= n; i++) {
		if(a[i] > b[i]) continue;
		int l = i, r = n + 2;
		while(r - l > 1) {
			int mid = (r + l) >> 1;
			if(geta(i, mid) > getb(i, mid)) r = mid;
			else l = mid;
		}
		int pr = r;
		l = i, r = n + 2;
		while(r - l > 1) {
			int mid = (r + l) >> 1;
			if(geta(i, mid) >= getb(i, mid)) r = mid;
			else l = mid;
		}
		ans += pr - r;
	}
	std::cout << ans << std::endl;
	return 0;
}
