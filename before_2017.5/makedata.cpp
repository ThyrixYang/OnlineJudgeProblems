#include <bits/stdc++.h>

using namespace std;

const int maxn=1e5;
const int maxm=1e3;
const int T = 1;
const int N = 1e5;
const int M = 1e5;
const int P = 1e5;
const int X = 1e5;
int main(){
	freopen("./in","w",stdout);
	srand(223434);
	for(int i = 0; i < T; i++) {
		printf("%d %d %d %d\n", N, M, X, P);
		for(int i = 0; i < N; i++) {
			int l = rand() % X + 1;
			int r = rand() % X + 1;
			if(l > r) std::swap(l, r);
			printf("%d %d %d\n", l, r, rand() % maxn);
		}
		for(int i = 0; i < M; i++) {
			printf("%d %d %d %d\n", rand() % maxn + 1, rand() % maxn + 1, 
					rand() % maxn + 1, rand() % N + 1);
		}
	}
	return 0;
}
