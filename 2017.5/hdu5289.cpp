#include <bits/stdc++.h>

using namespace std;

const int maxn=2e5;
int T,n,k;
int a[maxn];
int main(){
	freopen("./in","r",stdin);
	cin>>T;
	while(T--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		long long ans=0;
		map<int,int> M;
		int j=1;
		for(int i=1;i<=n;i++){
			while(M.empty()||(j<=n&&((--M.end())->first-M.begin()->first<k))){
				++M[a[j++]];
			}
			ans+=j-i-1;
			if(((--M.end())->first-M.begin()->first<k)) ans++;
			if(--M[a[i]]==0) M.erase(a[i]);
		}
		cout<<ans<<endl;
	}
	return 0;
}
