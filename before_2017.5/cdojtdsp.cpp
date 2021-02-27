#include <bits/stdc++.h>

using namespace std;

const int maxn=2005;
int n;
int a[4];
int p[maxn];
long long dp[maxn][4];
int sgn(int a,int b){
	if(a>b) return 1;
	else if(a<b) return -1;
	return 0;
}
int main(){
	freopen("./in","r",stdin);
	cin>>n;
	for(int i=0;i<4;i++) scanf("%d",&a[i]);
	for(int i=0;i<n;i++) scanf("%d",&p[i]);
	for(int i=0;i<n;i++) dp[i][0]=1;
	for(int i=1;i<4;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<j;k++){
				if(sgn(p[k],p[j])==sgn(a[i-1],a[i])) dp[j][i]+=dp[k][i-1];
			}
		}
	}
	long long ans=0;
	for(int i=0;i<n;i++) {
		ans+=dp[i][3];
		cout<<i<<" "<<dp[i][3]<<endl;
	}
	cout<<ans<<endl;
	return 0;
}
