#include <bits/stdc++.h>

using namespace std;

const int maxn=2000;
char s[100000];
int sgn[maxn];
int cnt=0;
int cntp=1;
int n;
int ans[maxn];
int maxv;
int main(){
	freopen("./in","r",stdin);
	sgn[1]=1;
	while(scanf("%s",s)!=EOF){
		if(s[0]=='?') cnt++;
		else if(s[0]=='+') sgn[cnt+1]=1,cntp++;
		else if(s[0]=='-') sgn[cnt+1]=-1;
		else sscanf(s,"%d",&n);
	}
	maxv=n;
	for(int i=1;i<=cnt;i++) ans[i]=1;
	int low=cntp-(cnt-cntp)*n;
	int up=cntp*n-(cnt-cntp)*1;
	if(n<=up&&n>=low){
		n-=cntp;
		n+=cnt-cntp;
		puts("Possible");
		for(int i=1;i<=cnt;i++){
			if(sgn[i]>0&&n>0) ans[i]+=min(maxv-1,n),n-=min(maxv-1,n);
			else if(sgn[i]<0&&n<0) ans[i]+=min(-n,maxv-1),n+=min(maxv-1,-n);
		}
		for(int i=1;i<=cnt;i++){
			if(i>1){
				if(sgn[i]==1) printf(" + ");
				else printf(" - ");
			}
			printf("%d",ans[i]);
		}
		printf(" = %d\n",maxv);
	}else{
		puts("Impossible");
	}
	return 0;
}
