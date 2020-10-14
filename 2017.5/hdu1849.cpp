#include <bits/stdc++.h>

int N;
int main() {
	freopen("in", "r", stdin);
	while(std::cin >> N, N){
		int res = 0;
		for(int i = 0; i < N; i++) {
			int x;
			scanf("%d", &x);
			res ^= x;
		}
		if(!res) puts("Grass Win!");
		else puts("Rabbit Win!");
	}
	return 0;
}