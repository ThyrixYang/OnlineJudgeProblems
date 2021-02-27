#include<bits/stdc++.h>

using namespace std;

const int maxn=1e6;
int n;
int a[maxn];
int main(){
	freopen("./in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		a[x]=i;
	}
	int ans=abs(a[1]-a[n]);
	ans=max(ans,abs(a[1]-n));
	ans=max(ans,abs(a[1]-1));
	ans=max(ans,abs(a[n]-n));
	ans=max(ans,abs(a[n]-1));
	cout<<ans<<endl;
	return 0;
}
