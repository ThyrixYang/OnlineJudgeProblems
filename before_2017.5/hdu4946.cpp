#include <bits/stdc++.h>

using namespace std;

#define se second
#define sq(x) ((x) * (x))

inline int sgn(int x){
	if(x < 0) return -1;
	if(x > 0) return 1;
	return 0;
}
struct Point{
	int x, y;
    int id;
	Point(int x = 0, int y = 0): x(x) ,y(y) {}
    void in() {scanf("%d%d", &x, &y);}
	Point operator - (const Point &C) const {
		return Point(x - C.x, y - C.y);
	}

	int operator ^ (const Point &C) const {
		return x * C.y - y * C.x;
	}

    int operator * (const Point &C) const {
        return x * C.x + y * C.y;
    }
};
inline int dist(const Point &A,const Point &B){
	return sq(A-B);
}
const int MAXN = 600;
Point List[MAXN];
int Stack[MAXN],top;
//相对于List[0]的极角排序
bool _cmp(const Point &p1,const Point &p2){
	int tmp = (p1-List[0])^(p2-List[0]);
	if(sgn(tmp) > 0)return true;
	else if(sgn(tmp) == 0 && sgn(dist(p1,List[0]) - dist(p2,List[0])) <= 0)
		return true;
	else return false;
}
void Graham(int n){
	Point p0;
	int k = 0;
	p0 = List[0];
//找最下边的一个点
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
			sgn((List[Stack[top-1]]-List[Stack[top-2]])^(List[i]-List[Stack[top-2]])) <
			0)
			top--;
		Stack[top++] = i;
	}
}
int n;
Point ps[MAXN];
int v[MAXN];
int ans[MAXN];
int cas;
struct Node {
    int x, y, v;
    Node(int x = 0, int y = 0, int v = 0): x(x) , y(y), v(v) {}
    bool operator < (const Node &C) const {
        if(x != C.x) return x < C.x;
        if(y != C.y) return y < C.y;
        return v < C.v;
    }
};
int main() {
	freopen("./in", "r", stdin);
    while(scanf("%d", &n) != EOF) {
        if(n == 0) break;
        std::map<Node, int> M;
        int maxv = 0;
        for(int i = 0; i < n; i++) {
            ps[i].in();
            scanf("%d", &v[i]);
            ps[i].id = i;
            ++M[Node(ps[i].x, ps[i].y, v[i])];
        }
        for(int i = 0; i < n; i++) {
            if(v[i] > maxv) {
                maxv = v[i];
            }
        }
        std::memset(ans, 0, sizeof ans);
        int h = 0;
        if(maxv == 0) {
            goto lab;
        }
        for(int i = 0; i < n; i++) {
            if(v[i] == maxv && M[Node(ps[i].x, ps[i].y, v[i])] == 1) {
                List[h++] = ps[i];
            }
        }
        top = 0;
        if(h) Graham(h);
        for(int i = 0; i < top; i++) {
            ans[List[Stack[i]].id] = 1;
        }
        lab:
        printf("Case #%d: ", ++cas);
        for(int i = 0; i < n; i++) printf("%d", ans[i]);
            puts("");
    }
    return 0;
}
