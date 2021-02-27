#include <bits/stdc++.h>

int n;
int main() {
	freopen("./in", "r", stdin);
	int c0 = 0, c1 = 0, c2 = 0;
	std::cin >> n;
	while(n--) {
		int x, y;
		scanf("%d%d", &x, &y);
		if(x > y) c0++;
		else if(x < y) c1++;
		else c2++;
	}
	if(c0 > c1) puts("Mishka");
	else if(c0 < c1) puts("Chris");
	else puts("Friendship is magic!^^");
	return 0;
}
