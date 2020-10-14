#include <bits/stdc++.h>

using namespace std;

const int maxn=5e5+3000;
double dp[maxn][61];
int q;
int id=2;
int fa[maxn];
double tmp[maxn];
int main(){
	freopen("./in","r",stdin);
	for(int i=0;i<=60;i++) dp[1][i]=1;
	cin>>q;
	while(q--){
		int t,v;
		scanf("%d%d",&t,&v);
		if(t==1){
			fa[id]=v;
			int u=id++;
			for(int i=0;i<=60;i++) dp[u][i]=1;
			double fore=dp[v][0];
			dp[v][0]*=0.5;
			u=v;
			for(int i=1;i<60;i++){
				int f=fa[u];
				double tmp=dp[f][i];
				dp[f][i]=(0.5+dp[u][i-1]*0.5)*dp[f][i]/(fore*0.5+0.5);
				fore=tmp;
				if(f==1) break;
				u=fa[u];
			}
		}else{
			double ans=0;
			for(int i=1;i<=60;i++) ans+=i*(dp[v][i]-dp[v][i-1]);
			printf("%.15f\n",ans);
		}
	}
	return 0;
}
