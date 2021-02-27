#include<bits/stdc++.h>

using namespace std;

int n;
char s[200];
int main() {
	freopen( "./in", "r", stdin );
	cin>>n;
	for( int i = 0; i < n; i++ ){
		scanf("%s" ,s);
		int a, b;
		scanf("%d%d", &a, &b);
		if(a >= 2400 && b > a) {
			puts("YES");
			return 0;
		}
	}
	puts("NO");
	return 0;
}
