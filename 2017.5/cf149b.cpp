#include <bits/stdc++.h>

char s[20];
long long convert(int l, int r, long long b) {
	long long ans = 0;
	long long bb = 1;
	for(int i = r; i >= l; i--) {
		long long c;
		if(isupper(s[i])) c = s[i] - 'A' + 10;
		else c = s[i] - '0';
		ans += bb * c;
		bb *= b;
	}
	return ans;
}
int getn(char c) {
	if(isupper(c)) return c - 'A' + 10;
	else return c - '0';
}
std::vector<int> ans;
int main() {
	freopen("./in", "r", stdin);
	scanf("%s", s);
	int len = strlen(s);
	int l1 = 0;
	int r1 = 0;
	for(; r1 < len; r1++) {
		if(s[r1] == ':') break;
	}
	int l2 = r1 + 1;
	r1--;
	int r2 = len - 1;
	int out = 0;
	for(int b = 2; b <= 1000; b++) {
		int f = 1;
		for(int i = l1; i <= r1; i++) if(getn(s[i]) >= b) f = 0;
		for(int i = l2; i <= r2; i++) if(getn(s[i]) >= b) f = 0;
		if(!f) continue;
		long long h = convert(l1, r1, b);
		long long m = convert(l2, r2, b);
		if(h >= 24 || m >= 60) f = 0;
		if(!f) continue;
		ans.push_back(b);
	}
	if(ans.size() == 0) puts("0");
	else if(ans.size() > 600) puts("-1");
	else {
		for(int i = 0; i < ans.size(); i++) {
			printf("%d ", ans[i]);
		}
	}
	return 0;
}
