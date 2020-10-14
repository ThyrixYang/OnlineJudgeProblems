#include <bits/stdc++.h>

using namespace std;

const int maxn=300;
const double EPS=1e-4;
int n,m;
double a[maxn][maxn];
int Gauss(){
	int now=0,maxr=-1,col=0;
	for(;col<m;col++){
		int k=now;
		for(int i=now;i<n;i++)
			if(fabs(a[i][col])>fabs(a[k][col])) k=i;
		if(fabs(a[k][col])<EPS) continue;
		maxr=now;
		for(int i=col;i<m;i++) swap(a[now][i],a[k][i]);
		for(int i=now+1;i<n;i++){
			double tmp=a[i][col]/a[now][col];
			for(int j=col;j<m;j++) a[i][j]-=a[now][j]*tmp;
		}
		now++;
	}
	return maxr+1;
}
int main(){
	freopen("./in","r",stdin);
	while(scanf("%d%d",&n,&m)!=EOF){
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				scanf("%lf",&a[i][j]);
		printf("%d\n",Gauss());
	}
	return 0;
}
