#include <bits/stdc++.h>

int T;
int a , b , c ;
int main() {
	std::cin >> T ;
	while( T-- ) {
		scanf("%d%d%d" , &a , &b , &c);
		int ans = 0;
		for(int x = 0 ; x <= c ; x++) {
			int aa = a - x;
			int bb = b - x;
			int p = x + 1;
			p = std::min( p , aa / 2 );
			p = std::min( p , bb );
			int d = aa - bb;
			int dx = std::min(d , p);
			for(int t = std::max(-3, -dx); t <= 3; t++) {
				int d = dx + t;
				if(d > p) break;
				aa = a - x;
				bb = b - x;
				aa -= d * 2;
				bb -= d;
				int cnt = d;
				if(aa > 0 && bb > 0) {
					int d = std::min(aa, bb) / 3;
					aa -= 3 * d;
					bb -= 3 * d;
					cnt += 2 * d;
				}
				if(cnt + 1 < x) continue;
				ans = std::max( ans , cnt + x );
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
