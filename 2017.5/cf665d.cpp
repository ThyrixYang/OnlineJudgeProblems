#include <bits/stdc++.h>

using namespace std;

const int maxn=1005;
const int maxv=2e6+30000;
int n;
int a[maxn];
int pri[maxv];
bool np[maxv];
void init(){
	for(int i=2;i<maxv;i++){
		if(!np[i]) pri[++pri[0]]=i;
		for(int j=1;j<=pri[0];j++){
			int x=pri[j];
			if(x*i>=maxv) break;
			np[x*i]=1;
			if(i%x==0) break;
		}
	}
}
int cnt1=0;
vector<int> out;
int main(){
	freopen("./in","r",stdin);
	init();
	cin>>n;
	int ans=1;
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
		if(a[i]==1) cnt1++;
		if(out.empty()) out.push_back(a[i]);
	}
	if(cnt1){
		int cnt=0;
		out.clear();
		for(int i=0;i<n;i++){
			if(!np[a[i]+1]){
				if(a[i]==1) out.push_back(1);
				else if(cnt==0) out.push_back(a[i]),cnt++;
			}
		}
		ans=max(ans,cnt+cnt1);
	}
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(!np[a[i]+a[j]]){
				if(ans<2){
					ans=2;
					out.clear();
					out.push_back(a[i]);
					out.push_back(a[j]);
				}
			}
		}
	}
	cout<<out.size()<<endl;
	for(int i=0;i<out.size();i++) cout<<out[i]<<" ";
	return 0;
}
