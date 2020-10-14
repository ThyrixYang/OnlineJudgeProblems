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
const int MAXN = 55;
const int MAXM = 105;
const int MAXT = 20005;
const int LEN = 1 << 17;
Complex X1[LEN], X2[LEN];
vector<int> G[MAXN];
int N, M, T, X;
double dp[MAXN][MAXT];
double sum[MAXN][MAXT];
int train[MAXM][3];
double td[MAXM][MAXT];
int dist[MAXN][MAXN];
void solve(int l, int r) {
	if(l > T) return;
	if(r - l <= 1) {
		for(int i = 1; i < N; i++) {
			double tmp = 1e30;
			for(int j = 0; j < (int) G[i].size(); j++) {
				int e = G[i][j];
				tmp = min(tmp, sum[e][l] + train[e][2]);
			}
			tmp = min(tmp, (double)dist[i][N] + X);
			dp[i][l] = tmp;
		}
		dp[N][l] = 0;
		return;
	}
	int mid = (r + l) >> 1;
	solve(mid, r);
	int len = LEN;
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < T; j++) {
			X1[T - j - 1] = Complex(td[i][j + 1], 0);
		}
		for(int j = T; j < len; j++) {
			X1[j] = Complex();
		}
		for(int j = mid; j < r; j++) {
			X2[j - mid] = Complex(dp[train[i][1]][j], 0);
		}
		for(int j = r - mid; j < len; j++) {
			X2[j] = Complex();
		}
		fft(X1, len, 1);
		fft(x2, len, 1);
		for(int j = 0; j < len; j++) {
			X1[j] = X1[j] * X2[j];
		}
		fft(X1, len, 1);
		
	}
	return;
}
int main() {
	freopen("./in", "r", stdin);
	memset(dist, 0x3f, sizeof dist);
	cin >> N >> M >> T >> X;
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < 3; j++) {
			scanf("%d", &train[i][j]);
		}
		dist[train[i][0]][train[i][1]] = 
			min(dist[train[i][0]][train[i][1]], train[i][2]);
		G[train[i][0]].push_back(i);
		for(int j = 1; j <= T; j++) {
			scanf("%lf", &td[i][j]);
			td[i][j] /= 1e5;
		}
	}
	for(int k = 1; k <= N; k++)
		dist[k][k] = 0;
	for(int k = 1; k <= N; k++) 
		for(int i = 1; i <= N; i++) 
			for(int j = 1; j <= N; j++) 
				dist[i][j] = min(dist[i][j], 
						dist[i][k] + dist[k][j]);
	for(int i = 1; i <= N; i++) {
		for(int j = T + 1; j <= T * 2 + 1; j++) {
			sum[i][j] = dist[i][N] + X;
		}
	}
	solve(0, (T + 1) * 2);
	printf("%.15f\n", dp[1][0]);
	for(int i = 1; i <= N; i++) {
		for(int j = 0; j <= T; j++) {
			printf("%.2f ", dp[i][j]);
		}
		puts("");
	}
	return 0;
}
