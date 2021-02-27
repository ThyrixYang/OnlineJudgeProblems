#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e5 + 3000;
const int MOD = 313;
const double PI = acos(-1.0);
struct Complex{
double x,y;
Complex(double _x = 0.0,double _y = 0.0){x = _x;y = _y;}
Complex operator -(const Complex &b)const{return Complex(x-b.x,y-b.y);}
Complex operator +(const Complex &b)const{return Complex(x+b.x,y+b.y);}
Complex operator *(const Complex &b)const{return Complex(x*b.x-y*b.y,x*b.y+y*b.x);}
};
void change(Complex y[],int len){
	int i,j,k;
	for(i = 1, j = len/2;i <len-1;i++){
		if(i < j)swap(y[i],y[j]);
		k = len/2;
		while(j >= k){
			j -= k;
			k /= 2;
		}
		if(j < k)j += k;
	}
}
void fft(Complex y[],int len,int on){
	change(y,len);
	for(int h = 2; h <= len; h <<= 1){
		Complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
		for(int j = 0;j < len;j+=h){
			Complex w(1,0);
			for(int k = j;k < j+h/2;k++){
				Complex u = y[k];
				Complex t = w*y[k+h/2];
				y[k] = u+t;
				y[k+h/2] = u-t;
				w = w*wn;
			}
		}
	}
	if(on == -1){
		for(int i = 0;i < len;i++)
			y[i].x /= len;
	}
}
int n;
int a[MAXN];
int dp[MAXN];
Complex x1[MAXN],x2[MAXN];
void solve(int l, int r) {
	if(r - l <= 1) return;
	int mid = (r + l) >> 1;
	solve(l, mid);
	int len = 1;
	while(len < (r - l) * 2) len <<= 1;
	for(int i = 0; i < len; i++) x1[i] = x2[i] = Complex();
	for(int i = 0; i < mid - l; i++) x1[i] = Complex(dp[l + i], 0);
	for(int i = 0; i < r - l; i++) x2[i] = Complex(a[i], 0);
	fft(x1, len, 1);
	fft(x2, len, 1);
	for(int i = 0; i < len; i++) x1[i] = x1[i] * x2[i];
	fft(x1, len, -1);
	for(int i = mid; i < r; i++) {
		dp[i] = dp[i] + x1[i - l].x + 0.5;
		dp[i] %= MOD;
	}
	solve(mid, r);
}
int main() {
	freopen("./in", "r", stdin);
	while(scanf("%d", &n)) {
		if(n == 0) break;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), dp[i] = 0;
		for(int i = 0; i <= n; i++) a[i] %= MOD;
		dp[0] = 1;
		solve(0, n + 3);
		printf("%d\n", dp[n]);
	}
	return 0;
}
