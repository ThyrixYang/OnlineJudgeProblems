#include <bits/stdc++.h>

using namespace std;

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
int fftm(Complex* t, Complex* x1, Complex* x2, int len1, int len2) {
	int len = 1;
	while(len < len1 + len2) len <<= 1;
	for(int i = len1; i < len; i++) x1[i] = Complex(0, 0);
	for(int i = len2; i < len; i++) x2[i] = Complex(0, 0);
	fft(x1, len, 1);
	fft(x2, len, 1);
	for(int i = 0; i < len; i++) t[i] = x1[i] * x2[i];
	fft(x1, len, -1);
	fft(x2, len, -1);
	return len;
}
const int MAXN = 1e5;
Complex x1[MAXN], x2[MAXN], tmp[MAXN];
int T;
int H, S; 
int len1, len2;
double Cal(int x, int y, int z) {
	z = H - z;
	cout << x << " " << y << " " << z << endl;
	if(z <= 0) return 1;
	int maxlen = 1;
	x1[0] = Complex(1, 0);
	len1 = 1;
	len2 = 1;
	while(len2 <= y) len2 <<= 1;
	while(maxlen <= max(z + 1, max(len1, len2)) * 2) maxlen <<= 1;
	for(int i = 1; i <= y; i++) {
		x2[i] = Complex(1.0 / y, 0);
	}
	x2[0] = Complex(0, 0);
	for(int i = y + 1; i < len2; i++) {
		x2[i] = Complex(0, 0);
	}
	while(x > 0) {
		if(x & 1) {
			int l = fftm(x1, x1, x2, len1, len2);
			if(l > maxlen) {
				for(int i = z + 1; i < l; i++) {
					x1[z].x += x1[i].x;
					x1[i].x = 0;
				}
				len1 = maxlen;
			} else {
				len1 = l;
			}
		}
		for(int i = 0; i < len2; i++) tmp[i] = x2[i];
		int l = fftm(x2, x2, tmp, len2, len2);
		if(l > maxlen) {
			for(int i = z + 1; i < l; i++) {
				x2[z].x += x2[i].x;
				x2[i].x = 0;
			}
			len2 = maxlen;
		} else {
			len2 = l;
		}
		for(int i = 0; i < len2; i++) x2[i] = tmp[i];
		x >>= 1;
	}
	double ans = 0;
	for(int i = z; i < len1; i++) ans += x1[i].x;
	puts("");
		puts("");
		puts("");
	for(int i = 0; i < len1; i++) printf("%.3f ", x1[i].x);
	puts("");
	return ans;
}
char s[20000];
int main() {
	freopen("../Data/stdin", "r", stdin);
	cin >> T;
	for(int cas = 1; cas <= T; cas++) {
		printf("Case #%d: ", cas);
		cin >> H >> S;
		double ans = 0;
		for(int i = 0; i < S; i++) {
			scanf("%s", s);
			int l = strlen(s);
			int p = 0;
			while(s[p] != 'd') p++;
			s[p] = 0;
			int p1 = p;
			int x = atoi(s);
			while(s[p] != '+' && s[p] != '-' && p < l) p++;
			int z = 0;
			if(p != l) z = atoi(s + p - 1);
			s[p] = 0;
			int y = atoi(s + p1 + 1);
			double tmp = Cal(x, y, z);
			ans = max(ans, tmp);
		}
		printf("%.10f\n", ans);
	}
	return 0;
}
