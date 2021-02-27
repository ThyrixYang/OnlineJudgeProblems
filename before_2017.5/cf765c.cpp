#include <bits/stdc++.h>

using namespace std;

long long k, a, b;

int main() {

	cin >> k >> a >> b;
	if(k > a && k > b) {
		puts("-1");
		return 0;
	}
	if(a % k != 0 && b < k) {
		puts("-1");
		return 0;
	}
	if(a < k && b % k != 0) {
		puts("-1");
		return 0;
	}
	cout << a / k + b / k << endl;
	return 0;
}
