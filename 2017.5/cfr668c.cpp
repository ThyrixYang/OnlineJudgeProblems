#include <bits/stdc++.h>

using namespace std;

const int maxn=1e6;
const double eps=1e-9;
int n;
double pmin[maxn],pmax[maxn];
double f[maxn],g[maxn];
double x[maxn][2],s[maxn][2];
int fore[maxn][2];
#define sq(x) ((x)*(x))
int main(){
	freopen("./in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%lf",&pmax[i]),pmax[i]+=pmax[i-1];
	for(int i=1;i<=n;i++) scanf("%lf",&pmin[i]),pmin[i]+=pmin[i-1];
	for(int i=1;i<=n;i++){
		double y=pmax[i];
		double z=pmin[i];
		if(y<1e-10){
			x[i][0]=0,x[i][1]=z;
			s[i][0]=z,s[i][1]=0;
		}else{
			x[i][0]=((z+y)+sqrt(sq(y+z)-4*y))/2;
			x[i][1]=((z+y)-sqrt(sq(y+z)-4*y))/2;
			if(sq(y+z)-4*y<=0) x[i][0]=x[i][1]=(z+y)/2;
			s[i][0]=y/x[i][0];
			s[i][1]=y/x[i][1];
			if(x[i][0]>=1+eps||s[i][0]>=1+eps) x[i][0]=x[i][1],s[i][0]=s[i][1];
			if(x[i][1]>=1+eps||s[i][1]>=1+eps||x[i][1]<1e-10) x[i][1]=x[i][0],s[i][1]=s[i][0];
		}
	}
	memset(fore,-1,sizeof fore);
	fore[0][0]=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<2;j++){
			if(fore[i][j]==-1) continue;
			for(int k=0;k<2;k++){
				if(x[i][j]<x[i+1][k]+eps&&s[i][j]<s[i+1][k]+eps){
					fore[i+1][k]=j;
				}
			}
		}
	}
	int p;
	if(fore[n][0]!=-1) p=0;
	else p=1;
	for(int i=n;i>=1;i--){
		f[i]=x[i][p];
		g[i]=s[i][p];
		p=fore[i][p];
	}
	for(int i=1;i<=n;i++) printf("%.15f ",f[i]-f[i-1]);
	puts("");
	for(int i=1;i<=n;i++) printf("%.15f ",g[i]-g[i-1]);
	return 0;
}
