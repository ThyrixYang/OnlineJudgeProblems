#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6;
int n;
int a, b, c;
int t[maxn];
int fa[maxn];
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
void change(int x) {
	if(find(x) == n) return;
	int y = find(x) + 1;
	fa[find(x)] = find(y);
}
int main() {
	freopen("./in", "r", stdin);
	cin >> n;
	cin >> a >> b >> c;
	if(a < b) swap(a, b);
	if(a < c) swap(a, c);
	if(b < c) swap(b, c);
	for(int i = 0; i < n; i++) {
		scanf("%d", &t[i]);
		fa[i] = i;
	}
	fa[n] = n;
	sort(t, t + n, greater<int>() );
	int sa = n, sb = n, sc = n;
	for(int i = n - 1; i >= 0; i--) {
		if(t[i] <= a) sa = i;
		if(t[i] <= b) sb = i;
		if(t[i] <= c) sc = i;
	}
	if(t[0] > a + b + c){
		puts("-1");
		return 0;
	}
	int ans = 0;
	for(;;) {
		int next = find(0);
		if(next == n) break;
		ans++;
		change(next);
		if(t[next] > a + b) {
		}else if(t[next] > a + c) {
			change(sc);
		}else if(t[next] > max(a, b + c)) {
			change(sb);
		}else if(t[next] > b) {
			if(t[next] > b + c || t[next] > a) {
				if(t[next] > b + c) change(sc), change(sb);
				else change(sa);
			}else{
				if(find(sb) == n) {
					change(sa);
				}else{
					change(sb);
					change(sc);
				}
			}
		}else if(t[next] > c) {
			change(sa);
			change(sc);
		}else {
			change(sa);
			change(sb);
		}
	}
	cout << ans << endl;
	return 0;
}
