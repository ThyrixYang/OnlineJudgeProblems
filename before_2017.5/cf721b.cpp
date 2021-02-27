#include <bits/stdc++.h>

const int MAXN = 1000;
int N, K;
int a[MAXN];
char s[MAXN];
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N >> K;
	for(int i = 0; i < N; i++) {
		scanf("%s", s);
		a[i] = strlen(s);
	}
	std::sort(a, a + N);
	scanf("%s", s);
	int clen = strlen(s);
	int c1 = 0;
	int c2 = 0;
	for(int i = 0; i < N; i++) {
		if(a[i] < clen) c1++;
		else if(a[i] == clen) c2++;
	}
	long long ans1 = c1 + c1 / K * 5 + 1;
	long long ans2 = c1 + c2 + (c1 + c2 - 1) / K * 5;
	std::cout << ans1 << " " << ans2 << std::endl;
	return 0;
}
