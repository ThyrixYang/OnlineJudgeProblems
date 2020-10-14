#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn=1e5+3000;
int n,k;
int a[maxn],b[maxn];
int main(){
	freopen("./in","r",stdin);
	cin>>n>>k;
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	for(int i=0;i<n;i++) scanf("%d",&b[i]);
	ll l=0,r=3e9+7;
	while(r-l>1){
		ll mid=(r+l)/2;
		ll c=0;
		for(int i=0;i<n;i++){
			ll need=(long long)a[i]*mid;
			if(need>b[i]) c+=need-b[i];
			if(c>k) break;
		}
		if(c>k) r=mid;
		else l=mid;
	}
	cout<<l<<endl;
	return 0;
}
