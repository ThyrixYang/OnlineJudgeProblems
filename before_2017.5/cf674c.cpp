#include <bits/stdc++.h>

using namespace std;

const int maxn=2e5+3000;
struct Line{
	double a,b;
	Line(double a=0,double b=0):a(a),b(b){}
	double get(double x){return a*x+b;}
};
//维护一个斜率递减的凸包
struct convexHull{
	Line stk[maxn];
	int top;
	convexHull():top(0){}
	void insert(double a,double b){
		while(top>1){
			Line &l1=stk[top-2],&l2=stk[top-1];
			if((l2.a-l1.a)*(b-l1.b)>=(a-l1.a)*(l2.b-l1.b)) top--;
			else break;
		}
		stk[top++]=Line(a,b);
	}
	double getVal(double x){
		int l=-1,r=top-1;
		while(r-l>1){
			int mid=(r+l)>>1;
			if(stk[mid].get(x)<=stk[mid+1].get(x)) r=mid;
			else l=mid;
		}
		return stk[r].get(x);
	}
}A[53];
int n,k;
int t[maxn];
double rev[maxn];
long long sum[maxn];
double ss[maxn];
int main(){
	freopen("./in","r",stdin);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>t[i];
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+t[i];
		rev[i]=rev[i-1]+1.0/t[i];
		ss[i]=ss[i-1]+(double)sum[i]/t[i];
	}
	double ans=ss[n];
	for(int i=1;i<=n;i++){
		A[1].insert(-sum[i],sum[i]*rev[i]);
		for(int j=2;j<=k;j++){
			double tmp=A[j-1].getVal(rev[i])+ss[i];
			//if(i==2&&j==2) cout<<tmp<<endl;
			if(i==n&&j==k) ans=tmp;
			A[j].insert(-sum[i],-ss[i]+tmp+sum[i]*rev[i]);
		}
	}
	printf("%.15f\n",ans);
	return 0;
}
