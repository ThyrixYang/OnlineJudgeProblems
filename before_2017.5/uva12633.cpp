#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define PB pop_back
#define fs first
#define se second
#define eps (1e-8)
#define INF (0x3f3f3f3f)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;


const double PI = acos(-1.0);
//复数结构体
struct Complex{
double x,y;//实部和虚部 x+yi
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
/*
* 做FFT
* len必须为2^k形式,
* on==1时是DFT,on==-1时是IDFT
*/
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
const int maxn=1<<18;
Complex x1[maxn],x2[maxn];
int T;
int R,C,N;
int r[maxn],c[maxn];
bool vis[maxn];
int cas=0;
int main(){
	freopen("/home/slyfc/vimFile/in","r",stdin);
	cin>>T;
	while(T--){
		scanf("%d%d%d",&R,&C,&N);
		fill(r+1,r+R+1,1);
		fill(c+1,c+C+1,1);
		memset(vis,0,sizeof vis);
		for(int i=0;i<N;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			x=R-x+1;
			r[x]=0,c[y]=0;
			vis[x+y]=1;
		}
		int len=1;
		while(len<=(R+C)) len<<=1;
		for(int i=0;i<=R;i++) x1[i]=Complex(r[i],0);
		for(int i=0;i<=C;i++) x2[i]=Complex(c[i],0);
		for(int i=R+1;i<len;i++) x1[i]=Complex();
		for(int i=C+1;i<len;i++) x2[i]=Complex();
		fft(x1,len,1);fft(x2,len,1);
		for(int i=0;i<len;i++) x1[i]=x1[i]*x2[i];
		fft(x1,len,-1);
		ll ans=0;
		for(int i=0;i<len;i++){
			if(vis[i]) continue;
			ans+=x1[i].x+0.5;
		}
		printf("Case %d: ",++cas);
		cout<<ans<<endl;
	}
	return 0;
}
