#include <bits/stdc++.h>

int n, a, b;
int t[2000];
const int up = 50000;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> n >> a >> b;
	int sum = 1, m = 1;
	t[0] = 1;
	int s = 1;
	if(b == 0 && a > 0) {
		t[1] = 1;
		sum = 2;
		s = 2;
	}
	int f = 1;
	for(int i = s; i < n; i++) {
		if(b) {
			t[i] = sum + 1;
			sum += t[i];
			m = t[i];
			if(t[i] > up) {
				f = 0;
				break;
			}
			b--;
		}else if(a) {
			t[i] = m + 1;
			m = t[i];
			sum += t[i];
			if(t[i] > up) {
				f = 0;
				break;
			}
			a--;
		}else {
			t[i] = 1;
		}
	}
	if(a || b || !f) {
		puts("-1");
		return 0;
	}
	for(int i = 0; i < n; i++) printf("%d ", t[i]);
	return 0;
}
