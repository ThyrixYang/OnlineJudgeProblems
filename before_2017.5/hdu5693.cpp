#include <bits/stdc++.h>

using namespace std;

const int maxn=305;

int T,n,m;
int a[maxn];
set<int> S;
int dp[maxn][maxn];
bool D(int x){
	return S.find(x)!=S.end();
}
bool ok[maxn][maxn];
int main(){
	freopen("./in","r",stdin);
	cin>>T;
	while(T--){
		S.clear();
		cin>>n>>m;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=m;i++){
			int x;
			scanf("%d",&x);
			S.insert(x);
		}
		memset(ok,0,sizeof ok);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(D(a[j]-a[i])) ok[i][j]=1;
			}
		}
		memset(dp,0,sizeof dp);
		for(int k=2;k<=n;k++){
			for(int i=1;i+k-1<=n;i++){
				int j=i+k-1;
				int &ans=dp[i][j];
				for(int x=i;x<=j;x++) ans=max(ans,dp[i][x]),ans=max(ans,dp[x][j]);
				for(int x=i;x<=j;x++) ans=max(ans,dp[i][x]+dp[x+1][j]);
				for(int x=i;x<j;x++)
					if(ok[x][j]&&dp[x+1][j-1]==j-x-1) ans=max(ans,dp[i][x-1]+j-x+1);
				for(int x=i+1;x<=j;x++)
					if(ok[i][x]&&dp[i+1][x-1]==x-i-1) ans=max(ans,dp[x+1][j]+x-i+1);
				for(int x=i+1;x<j;x++){
					if(a[j]-a[x]==a[x]-a[i]&&ok[x][j]&&dp[i+1][x-1]==x-i-1&&dp[x+1][j-1]==j-x-1)  ans=j-i+1;
				}
			}
		}
		cout<<dp[1][n]<<endl;
	}
	return 0;
}
