#include <bits/stdc++.h>

int T;
int a , b , c ;
int main(){
	std::cin >> T;
	while(T--) {
		scanf("%d%d%d", &a , &b , &c );
		int ans = 0;
		for(int x = 0; x <= c ; x++) {
			for(int z = 0; z <= std::min(b - x, a / 2); z++) {
				for(int y = 0; y <= std::min((b - x - z) / 2, a - x - 2 * z); y++) {
					if(x + z + 1 >= y && x + y + 1 >= z && y + z + 1 >= x) 
						ans = std::max(ans, x + y + z);
				}
			}
		}
		std::cout << ans << std::endl;
	}
	return 0;
}
