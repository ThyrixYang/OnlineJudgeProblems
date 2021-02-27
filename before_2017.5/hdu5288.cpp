#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn=2e5;
int R[maxn],L[maxn];
int pr[maxn],pl[maxn];
int a[maxn],n;
const long long mod=1e9+7;
int main(){
	freopen("./in","r",stdin);
	while(cin>>n){
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),L[i]=0,R[i]=n+1;
		for(int i=0;i<=1e4;i++)	pr[i]=n+1,pl[i]=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j*j<=a[i];j++){
				if(a[i]%j==0){
					L[i]=max(L[i],pl[j]);
					if(j*j!=a[i]){
						L[i]=max(L[i],pl[a[i]/j]);
					}
				}
			}
			pl[a[i]]=i;
		}
		long long ans=0;
		for(int i=n;i>=1;i--){
			for(int j=1;j*j<=a[i];j++){
				if(a[i]%j==0){
					R[i]=min(R[i],pr[j]);
					if(j*j!=a[i]){
						R[i]=min(R[i],pr[a[i]/j]);
					}
				}
			}
			pr[a[i]]=i;
			ans+=(i-(ll)L[i]-1)*(R[i]-(ll)i-1)%mod+(i-L[i])+(R[i]-i)-1;
			ans%=mod;
		}
		cout<<ans<<endl;
	}
	return 0;
}
