#include <bits/stdc++.h>

struct Point{
	int x, y;
	Point(int x = 0, int y = 0):x(x), y(y){}
	bool operator < (const Point &C) const {
		if(x != C.x) return x < C.x;
		return y < C.y;
	}
};
std::set<Point> S;
Point pos[10];
int n;
char s[100];
int main(){
	std::cin >> n;
	scanf("%s", s);
	pos[1] = Point(0, 0);
	pos[2] = Point(0, 1);
	pos[3] = Point(0, 2);
	pos[4] = Point(1, 0);
	pos[5] = Point(1, 1);
	pos[6] = Point(1, 2);
	pos[7] = Point(2, 0);
	pos[8] = Point(2, 1);
	pos[9] = Point(2, 2);
	pos[0] = Point(3, 1);
	for(int i = 0; i < 10; i++) S.insert(pos[i]);
	for(int drx = -3; drx <= 3; drx++) {
		for(int dry = -3; dry <= 3; dry++) {
			if(drx == 0 && dry == 0) continue;
			int f = 1;
			for(int i = 0; i < n; i++) {
				int c = s[i] - '0';
				Point p = pos[c];
				int dx = p.x + drx;
				int dy = p.y + dry;
				if(S.find(Point(dx, dy)) == S.end()) {
					f = 0;
					break;
				}
			}
			if(f){
				puts("NO");
				return 0;
			}
		}
	}
	puts("YES");
	return 0;
}
