#include <bits/stdc++.h>


using namespace std;
const long long MOD = 1e6 + 3;
long long qpow(long long a, long long p, long long MOD) {
	long long ans = 1;
	while(p > 0) {
		if(p & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return ans;
}
const double PI = acos(-1.0);
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
const long long MOD2 = sqrt(MOD) + 33;
Complex A[4][MAXN], B[MAXN];
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

long long N, M, P;
long long cntl[MAXN], cntr[MAXN];
long long tmp[MAXN];
const int len = (1 << 16);
int main() {
	freopen("./in", "r", stdin);
	std::cin >> N >> M >> P;
	cntl[0] = 1;
	for(int i = 'A'; i <= 'Z'; i++) cntr[i % M] += 1;
	int lenl = 0, lenr = 1;
	while(N > 0) {
		if(N & 1) {
			std::memset(tmp, 0, sizeof(long long) * len);
			long long pp = qpow(P, lenr, M);
			for(int i = 0; i < len; i++) {
				int t = i * pp % M;
				tmp[t] += cntl[i];
				if(tmp[t] >= MOD) tmp[t] -= MOD;
			}
			fft_multi(tmp, tmp, cntr, len);
			for(int i = 0; i < len; i++) {
				if(i < M) cntl[i] = tmp[i];
				else {
					int t = i % M;
					cntl[t] += tmp[i];
					if(cntl[t] >= MOD) cntl[t] -= MOD;
				}
			}
			lenl += lenr;
		}
		std::memset(tmp, 0, sizeof(long long) * len);
		long long pp = qpow(P, lenr, M);
		for(int i = 0; i < len; i++) {
			int t = i * pp % M;
			tmp[t] += cntr[i];
			if(tmp[t] >= MOD) tmp[t] -= MOD;
		}
		fft_multi(tmp, tmp, cntr, len);
		for(int i = 0; i < len; i++) {
			if(i < M) cntr[i] = tmp[i];
			else {
				int t = i % M;
				cntr[t] += tmp[i];
				if(cntr[t] >= MOD) cntr[t] -= MOD;
			}
		}
		lenr *= 2;
		N >>= 1;
	}
	long long ans = 0;
	long long inv2 = qpow(2, MOD - 2, MOD);
	for(int i = 0; i < M; i++) {
		ans += cntl[i] * (cntl[i] - 1 + MOD) % MOD * inv2 % MOD;
		ans %= MOD;
	}
	std::cout << ans << std::endl;
	return 0;
}
