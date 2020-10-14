#include <bits/stdc++.h>

using namespace std;

int n;
priority_queue<int, vector<int>, greater<int> > Q;
int main() {
	freopen("./in","r",stdin);
	cin >> n;
	int t = 1;
	for(int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		Q.push(x);
	}
	for(int i = 0; i < n; i++) {
		int x = Q.top();
		Q.pop();
		if(x >= t) t++;
	}
	cout << t << endl;
	return 0;
}
