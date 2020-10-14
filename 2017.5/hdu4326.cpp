#include <bits/stdc++.h>

using namespace std;

#define eps 1e-9

const int MAXN=220;
double a[MAXN][MAXN],x[MAXN];//方程的左边的矩阵和等式右边的值,求解之后x存的就是结果
int equ,var;//方程数和未知数个数
/*
 *返回0表示无解,1表示有解
 */
int Gauss()
{
	int i,j,k,col,max_r;
	for(k=0,col=0;k<equ&&col<var;k++,col++)
	{
		max_r=k;
		for(i=k+1;i<equ;i++)
			if(fabs(a[i][col])>fabs(a[max_r][col]))
				max_r=i;
		if(fabs(a[max_r][col])<eps)return 0;
		if(k!=max_r)
		{
			for(j=col;j<var;j++)
				swap(a[k][j],a[max_r][j]);
			swap(x[k],x[max_r]);
		}
		x[k]/=a[k][col];
		for(j=col+1;j<var;j++)a[k][j]/=a[k][col];
		a[k][col]=1;
		for(i=0;i<equ;i++)
			if(i!=k)
			{
				x[i]-=x[k]*a[i][k];
				for(j=col+1;j<var;j++)a[i][j]-=a[k][j]*a[i][col];
				a[i][col]=0;
			}
	}
	return 1;
}
int T,cas=0;
int N,M,K;
int main(){
	freopen("/home/slyfc/vimFile/in","r",stdin);
	cin>>T;
	while(T--){
		printf("Case #%d: ",++cas);
		scanf("%d%d%d",&N,&M,&K);
		if(M==1){
			if(K<=4) puts("0.250000");
			else puts("0.000000");
			continue;
		}
		double p=0.25;
		memset(a,0,sizeof a);memset(x,0,sizeof x);
		var=N*(M+1);
		int &e=equ;
		e=0;
		for(int i=1;i<N;i++) a[e][i*(M+1)+M]=1,x[e]=0,e++;
		a[e][M]=1,x[e]=1,e++;
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				a[e][i*(M+1)+j]+=1;
				if(i==0) a[e][i*(M+1)+j+1]+=-p,a[e][(N-3)*(M+1)+1]+=-(1-p);
				if(i==1) a[e][(N-3)*(M+1)+j+1]+=-p,a[e][1]+=-p,a[e][(N-2)*(M+1)+1]+=-p*2;
				if(i==2) a[e][(N-2)*(M+1)+j+1]+=-p,a[e][1]+=-p,a[e][(N-2)*(M+1)+1]+=-p,a[e][(N-1)*(M+1)+1]+=-p;
				if(i==3) a[e][(N-1)*(M+1)+j+1]+=-p,a[e][1]+=-p,a[e][(N-1)*(M+1)+1]+=-p*2;
				if(i>3) a[e][(i-3)*(M+1)+j+1]+=-p,a[e][(i-3)*(M+1)+1]+=-(1-p);
				e++;
			}
		}
		int res=Gauss();
		printf("%.6f\n",x[(K-1)*(M+1)]);
	}
	return 0;
}
