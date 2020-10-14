#include <bits/stdc++.h>

using namespace std;

struct Line{
	double a,b;
	double get(double x){return a*x+b;}
	Line(double a=0,double b=0):a(a),b(b){}
};
const int maxn=3e5;
///求最小值，斜率递减
struct CH{
	Line stk[maxn];
	int top;
	CH():top(0){}
	void insert(double a,double b){
		while(top>1){
			Line &l1=stk[top-2],&l2=stk[top-1];
			if((b-l1.b)*(l2.a-l1.a)<=(l2.b-l1.b)*(a-l1.a)) top--;
			else break;
		}
		stk[top++]=Line(a,b);
	}
	double cal(double x){
		int l=-1,r=top-1;
		while(r-l>1){
			int mid=(r+l)>>1;
			if(stk[mid].get(x)<=stk[mid+1].get(x)) r=mid;
			else l=mid;
		}
		return stk[r].get(x);
	}
}C[60];
int n,k;
double t[maxn];
double sum[maxn],ss[maxn];
double dp[maxn][60];
int main(){
	freopen("./in","r",stdin);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>t[i];
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+t[i];
		ss[i]=sum[i]/t[i]+ss[i-1];
	}
	for(int i=1;i<=n;i++){
		C[1].insert(-sum[i],i*sum[i]);
		cout<<i<<" "<<-sum[i]<<" "<<i*sum[i]<<endl;
		for(int j=2;j<=min(i,k);j++){
			double res=C[j-1].cal(i)+ss[i];
			dp[i][j]=res;
			cout<<res<<endl;
			C[j].insert(-sum[i],dp[i][j]-ss[i]+i*sum[i]);
		}
	}
	printf("%.15f\n",dp[n][k]);
	return 0;
}
