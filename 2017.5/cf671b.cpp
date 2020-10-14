#include <bits/stdc++.h>

using namespace std;

const int maxn=6e5;
int n,k;
int a[maxn];
int main(){
	cin>>n>>k;
	long long sum=0;
	for(int i=0;i<n;i++) scanf("%d",&a[i]),sum+=a[i];
	sort(a,a+n);
	long long l=0,r=1e9+7;
	while(r-l>1){
		int mid=(r+l)>>1;
		long long cost=0;
		for(int i=0;i<n;i++) cost+=max(mid-a[i],0);
		if(cost<=k) l=mid;
		else r=mid;
	}
	for(int i=0;i<n;i++) a[i]=max((long long)a[i],l);
	l=0,r=1e9+7;
	while(r-l>1){
		int mid=(r+l)>>1;
		long long cost=0;
		for(int i=0;i<n;i++) cost+=max(a[i]-mid,0);
		if(cost<=k) r=mid;
		else l=mid;
	}
	for(int i=0;i<n;i++) a[i]=min((long long)a[i],r);
	if(a[n-1]==a[0]){
		if(sum%n==0) puts("0");
		else puts("1");
	}else{
		cout<<a[n-1]-a[0]<<endl;
	}
	return 0;
}
