#include <bits/stdc++.h>

using namespace std;
const long double PI = acos(-1.0);
const long long MOD = 1e9 + 7;
const long long MOD2 = 32000;
long long qpow(long long a, long long p) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
long long N, K;
struct Complex{
long double x,y;
Complex(long double _x = 0.0,long double _y = 0.0){x = _x;y = _y;}
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
const int MAXN = 1e5;
Complex A[4][MAXN];
Complex B[MAXN];
Complex X1[MAXN];
long long fac[MAXN], inv[MAXN];
void fft_multi(long long *x, long long *y, long long *z, int len) {
	for(int i = 0; i < len; i++) {
		A[0][i] = Complex(y[i] / MOD2, 0);
		A[1][i] = Complex(y[i] % MOD2, 0);
		A[2][i] = Complex(z[i] / MOD2, 0);
		A[3][i] = Complex(z[i] % MOD2, 0);
	}
	for(int i = 0; i < 4; i++) fft(A[i], len, 1);
	for(int i = 0; i < len; i++) {
		B[i] = A[0][i] * A[3][i] + A[1][i] * A[2][i];
		A[0][i] = A[0][i] * A[2][i];
		A[1][i] = A[1][i] * A[3][i];
	}
	fft(B, len, -1); fft(A[0], len, -1); fft(A[1], len, -1);
	for(int i = 0; i < len; i++) {
		x[i] = (long long)(B[i].x + 0.5) % MOD * MOD2 % MOD;
		x[i] = (x[i] + (long long)(A[0][i].x + 0.5)
				% MOD * MOD2 % MOD * MOD2 % MOD) % MOD;
		x[i] = (x[i] + (long long)(A[1][i].x + 0.5)) % MOD;
	}
}
int len = (1 << 16);
long long cntx[MAXN], cnty[MAXN];
long long tmp[MAXN];
int main() {
	freopen("./in", "r", stdin);
	fac[0] = inv[0] = 1;
	for(int i = 1; i < MAXN; i++) {
		fac[i] = fac[i - 1] * i % MOD;
		inv[i] = qpow(fac[i], MOD - 2);
	}
	std::cin >> N >> K;
	if(N > K) {
		puts("0");
		return 0;
	}
	long long lenl = 0, lenr = 1;
	cntx[0] = 1;
	for(int i = 1; i <= K; i++) {
		cnty[i] = 1;
		//cnty[i] = fac[K] * inv[K - i] % MOD * inv[i] % MOD;
	}
	while(N > 0) {
		if(N & 1) {
			for(int i = 0; i <= K; i++) {
				cntx[i] = (cntx[i] * inv[i] % MOD * qpow(2, i * lenr) % MOD);
				tmp[i] = cnty[i] * inv[i] % MOD;
			}
			fft_multi(tmp, cntx, tmp, len);
			for(int i = 0; i <= K; i++) cntx[i] = tmp[i] * fac[i] % MOD;
			for(int i = K + 1; i < len; i++) tmp[i] = 0;
			lenl += lenr;
		}
		for(int i = 0; i <= K; i++) {
			tmp[i] = cnty[i] * inv[i] % MOD * qpow(2, i * lenr) % MOD;
			cnty[i] = cnty[i] * inv[i] % MOD;
		}
		fft_multi(tmp, tmp, cnty, len);
		for(int i = K + 1; i < len; i++) tmp[i] = 0;
		for(int i = 0; i <= K; i++) {
			cnty[i] = tmp[i] * fac[i] % MOD;
		}
		lenr *= 2;
		N >>= 1;
	}
	long long ans = 0;
	for(int i = 0; i < len; i++) {
		ans = (ans + cntx[i] * fac[K] % MOD * inv[K - i] % MOD * inv[i] % MOD) % MOD;
	}
	std::cout << ans << std::endl;
	return 0;
}
