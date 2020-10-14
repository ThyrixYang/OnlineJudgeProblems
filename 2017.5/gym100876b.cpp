#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define eps (1e-8)
int sgn(double x){
	if(fabs(x)<eps) return 0;
	if(x<0) return -1;
	return 1;
}
int n,m;
int a[50][50];
ll sum[50][50];
bool used[50][50][50][50];
ll get(int x1,int y1,int x2,int y2){
	double k=((double)y1-y2)/(x1-x2);
	double b=-k*x1+y1;
	ll ans=0;
	bool flag = 0;
	for(int i=1;i<=n;i++){
		double low=k*(i-1)+b;
		double up=k*i+b;
		if(low>up) swap(low,up);
		int l=floor(low+eps);
		int r=ceil(up-eps);
		if(r<0 || l>m)
		{
			if(!flag)
				continue;
			break;
		}
		flag = 1;
		r=min(m,r);
		l=max(l,0);
		ans+=sum[i][r]-sum[i][l];
		if(sgn(l-low)==0&&l>0) ans+=a[i][l];
		if(r<m&&sgn(up-r)==0) ans+=a[i][r+1];
	}
	return ans;
}
int main(){
	//freopen("/home/cwind/vimFile/in","r",stdin);
	freopen("division.in","r",stdin);
	freopen("division.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
			sum[i][j]=sum[i][j-1]+a[i][j];
		}
	ll ans=0;
	//get(0,0,2,1);
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int x=0;x<=n;x++){
				for(int y=0;y<=m;y++){
					if(i!=x&&j!=y && !used[i][j][x][y] && !used[x][y][i][j])
					{
						ans=max(ans,get(i,j,x,y));
						int dx = x - i, dy = y - j;
						int gcd = __gcd(abs(dx), abs(dy));
						dx /= gcd;
						dy /= gcd;
						int tx = x, ty = y;
						while(tx >= 0 && tx <= n && ty >= 0 && ty <= m)
						{
							tx -= dx;
							ty -= dy;
						}
						tx += dx;
						ty += dy;
						for(;tx >= 0 && tx <= n && ty >= 0 && ty <= m; tx += dx, ty += dy)
							for(int tx2 = tx + dx, ty2 = ty + dy;
							tx2 >= 0 && tx2 <= n && ty2 >= 0 && ty2 <= m; tx2 += dx, ty2 += dy)
							used[tx][ty][tx2][ty2] = 1;
					}
				}
			}
		}
	}
	for(int i=2;i<=n;i++) ans=max(ans,sum[i][m]+sum[i-1][m]);
	for(int j=2;j<=m;j++){
		ll tmp=0;
		for(int i=1;i<=n;i++){
			tmp+=a[i][j];
			tmp+=a[i][j-1];
		}
		ans=max(ans,tmp);
	}
	printf("%lld",ans);
	return 0;
}
