#include <bits/stdc++.h>

int main() {
	int a;
	std::cin >> a;
	if(a & 1) {
		std::cout << a / 2 + 1 << std::endl;
	}else {
		std::cout << a/ 2 << std::endl;
	}
	return 0;
}
