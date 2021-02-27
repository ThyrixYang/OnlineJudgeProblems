#include <bits/stdc++.h>

using namespace std;

int a[]={1234567,123456,1234};
bool dfs(int v,int p){
	if(p==2) return v%a[2]==0;
	for(;v>=0;v-=a[p]){
		if(dfs(v,p+1)) return 1;
	}
	return 0;
}
int n;
int main(){
	freopen("./in","r",stdin);
	cin>>n;
	if(dfs(n,0)) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}
