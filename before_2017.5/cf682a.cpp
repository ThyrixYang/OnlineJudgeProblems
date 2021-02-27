#include <bits/stdc++.h>

using namespace std;

long long n,m;
int main(){
	freopen("./in","r", stdin);
	cin >> n >> m;
	long long  ans = 0;
	for(int i = 1; i <= n; i++) {
		int x = m;
		while( (x + i) % 5 != 0 && x > 0) x--;
		ans += (x + 4) / 5;
	}
	cout << ans << endl;
	return 0;
}
