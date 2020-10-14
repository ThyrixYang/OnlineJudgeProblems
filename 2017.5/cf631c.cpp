#include <bits/stdc++.h>

using namespace std;

const int maxn=1e6;
int n,m;
int a[maxn];
int ans[maxn];
int last[maxn];
int x[maxn],y[maxn];
int top=0;
int main(){
	freopen("./in","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		while(top>0&&y[top-1]<=b) top--;
		x[top]=a;
		y[top]=b;
		top++;
	}
	for(int i=0;i<top;i++) last[y[i]]=x[i];
	for(int i=n-1;i>=1;i--)
		if(last[i]==0) last[i]=last[i+1];
	int i=n;
	for(;i>=1;i--){
		if(last[i]) break;
		ans[i]=a[i];
	}
	sort(a+1,a+i+1);
	int l=1,r=i;
	for(;i>=1;i--){
		if(last[i]==1) ans[i]=a[r--];
		else ans[i]=a[l++];
	}
	for(int i=1;i<=n;i++) 
		printf("%d ",ans[i]);
	return 0;
}
