#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn=1e6;
int n;
ll a[maxn];
map<ll,int> M;
int main(){
	freopen("./in","r",stdin);
	cin>>n;
	ll sum=0;
	int ans=1;
	for(int i=0;i<n;i++){
		cin>>a[i];
		sum+=a[i];
		ans=max(ans,++M[sum]);
	}
	cout<<n-ans<<endl;
	return 0;
}
