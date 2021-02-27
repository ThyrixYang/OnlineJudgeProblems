#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn=1e5;
int n;
ll a[maxn],r,k;
int cas=0;
int main(){
	freopen("./in","r",stdin);
	while(scanf("%d%lld%lld",&n,&r,&k)){
		if(n==0&&r==0&&k==0) break;
		printf("Case %d:\n",++cas);
		if(r==2) k=n-k+1;
		int ed=(r-1)*n+k-1;
		for(int i=0;i<n*2;i++) scanf("%lld",&a[i]);
		reverse(a+n,a+n*2);
		int p=(ed+1+n*2)%(n*2);
		ll ansp=ed;
		while(p!=ed&&a[(p-1+n*2)%(n*2)]>a[p]){
			if(p>=n) ansp=p;
			p=(p+1+n*2)%(n*2);
		}
		if(ansp>=n){
			int f=1;
			ll sum=a[ansp];
			ll x=a[ansp]+1;
			if(ansp!=ed)
			for(int i=(ansp-1+n*2)%(n*2);;i=(i-1+n*2)%(n*2)){
				sum+=x;
				a[i]-=x;
				if(i==ed) break;
			}
			int p=(ed-1+n*2)%(n*2);
			while(p!=ansp){
				if(a[p]<x-1){
					f=0;
					break;
				}
				sum+=x-1;
				a[p]-=x-1;
				p=(p-1+n*2)%(n*2);
			}
			a[ansp]=sum;
			if(!f){
				puts("INVALID");
			}else{
				reverse(a+n,a+n*2);
				for(int i=0;i<n;i++) printf("%lld ",a[i]);
				puts("");
				for(int i=n;i<n*2;i++) printf("%lld ",a[i]);
				puts("");
			}
		}else{
			puts("INVALID");
		}
	}
	return 0;
}
