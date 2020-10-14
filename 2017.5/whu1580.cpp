#include <bits/stdc++.h>

using namespace std;

#define INF (0x3f3f3f3f)
const int maxn=10000;
int n,m,l;
int a[maxn],b[maxn];
int dp[maxn][20];
int main(){
	freopen("/home/cwind/vimFile/in","r",stdin);
	while(cin>>n>>m>>l){
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++) b[i]=b[i-1]^a[i];
		memset(dp,-1,sizeof dp);
		dp[0][0]=INF;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				for(int k=i-1;k>=max(0,i-l);k--){
					int val=b[i]^b[k];
					int tmp=min(val,dp[k][j-1]);
					dp[i][j]=max(dp[i][j],tmp);
				}
			}
		}
		cout<<dp[n][m]<<endl;
	}
	return 0;
}
