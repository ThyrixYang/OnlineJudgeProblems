#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5;
struct Point {
	ll x, y;
	Point (ll x = 0, ll y = 0) : x(x), y(y) {}
	void in() { scanf("%lld%lld", &x, &y); }
	ll operator ^ (const Point &C) const {
		return x * C.y - y * C.x;
	}
	Point operator - (const Point &C) const {
		return Point (x - C.x, y - C.y);
	}
	Point operator + (const Point &C) const {
		return Point (x + C.x, y + C.y);
	}
	void out() { printf("%lld %lld\n", x, y); }
};
ll sgn(ll x) {
	return x;
}
#define sq(x) ((x)*(x))
ll dist(Point a, Point b) {
	return sq(a.x - b.x) + sq(a.y - b.y);
}
const int MAXN = 1e5 + 300;
Point List[MAXN];
int Stack[MAXN], top;
//相对于List[0]的极角排序
bool _cmp(Point p1,Point p2){
	ll tmp = (p1-List[0])^(p2-List[0]);
	if(sgn(tmp) > 0)return true;
	else if(sgn(tmp) == 0 && sgn(dist(p1,List[0]) - dist(p2,List[0])) <= 0)
		return true;
	else return false;
}
void Graham(int n){
	Point p0;
	int k = 0;
	p0 = List[0];
	for(int i = 1;i < n;i++){
		if( (p0.y > List[i].y) || (p0.y == List[i].y && p0.x > List[i].x) ){
			p0 = List[i];
			k = i;
		}
	}
	swap(List[k],List[0]);
	sort(List+1,List+n,_cmp);
	if(n == 1){
		top = 1;
		Stack[0] = 0;
		return;
	}
	if(n == 2){
		top = 2;
		Stack[0] = 0;
		Stack[1] = 1;
		return ;
	}
	Stack[0] = 0;
	Stack[1] = 1;
	top = 2;
	for(int i = 2;i < n;i++){
		while(top > 1 &&
			sgn((List[Stack[top-1]]-List[Stack[top-2]])^(List[i]-List[Stack[top-2]])) <= 0)
			top--;
		Stack[top++] = i;
	}
}

ll area(int p1, int p2, int p3) {
	return abs( (List[Stack[p2]] - List[Stack[p1]]) ^ (List[Stack[p3]] - List[Stack[p1]]) );
}
int n;
ll S;
int main() {
	freopen("./in", "r", stdin);
	cin >> n >> S;
	for(int i = 0; i < n; i++)
		List[i].in();
	Graham(n);
	ll maxArea = 0;
	int resa, resb, resc;
	for(int a = 0; a < top; a++) {
		int c = (a + 2) % top;
		for(int b = (a + 1) % top; b != a ; b = (b + 1) % top) {
			while((c + 1) % top != a && area(a, b, (c + 1) % top) >= area(a, b, c)) {
				c = (c + 1) % top;
			}
			if(area(a, b, c) > maxArea) {
				maxArea = area(a, b, c);
				resa = a, resb = b, resc = c;
			}
		}
	}
	Point p1 = List[Stack[resa]];
	Point p2 = List[Stack[resb]];
	Point p3 = List[Stack[resc]];
	Point p11 = p1 + p2 - p3;
	Point p22 = p1 + p3 - p2;
	Point p33 = p2 + p3 - p1;
	p11.out();
	p22.out();
	p33.out();
	return 0;
}
