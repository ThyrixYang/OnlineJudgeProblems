#include <bits/stdc++.h>

int t;
int h, m;
int dis(int h1, int m1, int h2, int m2) {
	int ans = 0;
	if(h1 % 10 != h2 % 10) ans++;
	h1 /= 10, h2 /= 10;
	if(h1 != h2) ans++;
	if(m1 % 10 != m2 % 10) ans++;
	m1 /= 10, m2 /= 10;
	if(m1 != m2) ans++;
	return ans;
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> t;
	if(t == 12) {
		scanf("%d:%d", &h, &m);
		int ansh, ansm, ansd = 1e9;
		for(int i = 1; i <= 12; i++) {
			for(int j = 0; j < 60; j++) {
				if(dis(i, j, h, m) < ansd) {
					ansh = i, ansm = j;
					ansd = dis(i, j, h, m);
				}
			}
		}
		printf("%02d:%02d", ansh, ansm);
	} else {
		scanf("%d:%d", &h, &m);
		int ansh, ansm, ansd = 1e9;
		for(int i = 0; i < 24; i++) {
			for(int j = 0; j < 60; j++) {
				if(dis(i, j, h, m) < ansd) {
					ansh = i, ansm = j;
					ansd = dis(i, j, h, m);
				}
			}
		}
		printf("%02d:%02d", ansh, ansm);
	}
	return 0;
}
