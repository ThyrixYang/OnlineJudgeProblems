#include <bits/stdc++.h>

const int MAXN = 1e5;
const int MAXM = 2e6;
int N;
int a[MAXN];
std::vector<int> b[MAXN];
int dic[MAXM], dh;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N;
	for(int i = 0; i < N; i++) scanf("%d", &a[i]);
	std::sort(a, a + N);
	for(int i = 0; i < N; i++) {
		int x = a[i];
		while(x > 0) {
			b[i].push_back(x);
			dic[dh++] = x;
			x /= 2;
		}
	}
	std::sort(dic, dic + dh);
	dh = std::unique(dic, dic + dh) - dic;
	/*for(int i = 0; i < N; i++) {
		for(int j = 0; j < b[i].size(); j++) {
			printf("%d ", b[i][j]);
		}
		puts("");
	}
	for(int i = 0; i < dh; i++) {
		printf("%d ", dic[i]);
	}
	puts("");*/
	int l = -1, r = dh - 1;
	while(r - l > 1) {
		int mid = (r + l) >> 1;
		std::set<int> S;
		for(int i = 0; i <= mid; i++) {
			S.insert(dic[i]);
		}
		int f = 1;
		for(int i = 0; i < N; i++) {
			int c = -1;
			for(int j = b[i].size() - 1; j >= 0; j--) {
				int x = b[i][j];
				if(x > dic[mid]) break;
				if(S.find(x) != S.end()) {
					c = x;
				}
			}
			if(c == -1) {
				f = 0;
				break;
			}
			S.erase(c);
		}
		if(f) r = mid;
		else l = mid;
	}
	std::set<int> S;
	for(int i = 0; i <= r; i++) {
		S.insert(dic[i]);
	}
	for(int i = 0; i < N; i++) {
		int c = -1;
		for(int j = b[i].size() - 1; j >= 0; j--) {
			int x = b[i][j];
			if(x > dic[r]) break;
			if(S.find(x) != S.end()) {
				c = x;
			}
		}
		S.erase(c);
		printf("%d ", c);
	}
	return 0;
}
