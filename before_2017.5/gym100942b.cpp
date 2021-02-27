#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxv=10;
const int msz=maxv*maxv;
const ll mod=1e9+9;
int calsz=msz;
struct matrix{
	ll a[msz][msz];
	matrix(){memset(a,0,sizeof a);}
	void out(){
		for(int i=0;i<calsz;i++){
			for(int j=0;j<calsz;j++){
				cout<<a[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	void toI(){
		for(int i=0;i<calsz;i++)
			a[i][i]=1;
	}
};
matrix multi(matrix a,matrix b){
	matrix c;
	for(int i=0;i<calsz;i++)
		for(int j=0;j<calsz;j++)
			for(int k=0;k<calsz;k++)
				c.a[i][j]=(a.a[i][k]*b.a[k][j]+c.a[i][j])%mod;

	return c;
}
matrix mqpow(matrix a,ll p){
	matrix ans;
	ans.toI();
	while(p>0){
		if(p&1) ans=multi(ans,a);
		a=multi(a,a);p>>=1;
	}
	return ans;
}

ll n,m;
ll c[20];
int f(int x,int y){
	return x*m+y;
}
matrix t;
void build(){
	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++){
			for(int x=1;x<=m;x++){
				if(i==0&&j==0){
					for(int y=1;y<=m;y++){
						t.a[f(x-1,y-1)][f(0,0)]+=c[x]*c[y]%mod;
						t.a[f(x-1,y-1)][f(0,0)]%=mod;
					}
				}else if(i==0){
					t.a[f(x-1,j-1)][f(i,j)]+=c[x];
					t.a[f(x-1,j-1)][f(i,j)]%=mod;
				}else if(j==0){
					t.a[f(i-1,x-1)][f(i,j)]+=c[x];
					t.a[f(i-1,x-1)][f(i,j)]%=mod;
				}
			}
			if(i>0&&j>0){
				t.a[f(i-1,j-1)][f(i,j)]++;
				t.a[f(i-1,j-1)][f(i,j)]%=mod;
			}
			if(i==0&&j==0) (t.a[0][0]+=c[2])%mod;
		}
	}
}
int main(){
	freopen("/home/cwind/vimFile/in","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>c[i];
	calsz=m*m;
	build();
	matrix res=mqpow(t,n);
	cout<<res.a[0][0]<<endl;
	return 0;
}
