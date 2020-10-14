#include <bits/stdc++.h>

using namespace std;
const double PI = acos(-1.0);
const int len = 2048;
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
const int MAXN = 500;
int N, M, R, C;
Complex x1[len], x2[len];
char B[MAXN][MAXN];
char T[MAXN][MAXN];
int bb[26][MAXN][MAXN];
int tt[26][MAXN][MAXN];
int cnv[26][MAXN][len];
int main() {
	
	freopen("../Data/stdin", "r", stdin);

	cin >> N >> M;
	for(int i = 0; i < N; i++) {
		scanf("%s", B[i]);
		for(int j = 0; j < M; j++) {
			bb[B[i] - 'a'][i][j] = 1;
		}
	}
	cin >> R >> C;
	for(int i = 0; i < R; i++) {
		scanf("%s", T[i]);
		for(int j = 0; j < C; j++) {
			if(T[j] == '?') {
				for(int k = 0; k < 26; k++) {
					tt[k][i][j] = 1;
				}
			} else {
				tt[T[j] - 'a'][i][j] = 1;
			}
		}
	}
	for(int i = 0; i < 
	return 0;
}
