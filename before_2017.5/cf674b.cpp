#include<bits/stdc++.h>

using namespace std;

const int maxn=10000;
int n,k;
int a,b,c,d;
int m[maxn];
int main(){
	freopen("./in","r",stdin);
	cin>>n>>k;
	cin>>a>>b>>c>>d;
	m[1]=a;m[2]=c;m[n-1]=d;m[n]=b;
	int cnt=1;
	for(int i=1;i<=n;i++){
		while(cnt==a||cnt==b||cnt==c||cnt==d) cnt++;
		if(!m[i]) m[i]=cnt++;
	}
	//for(int i=1;i<=n;i++) cout<<m[i]<<endl;
	if(k<n-1+2){
		puts("-1");
		return 0;
	}
	if(n==4){
		puts("-1");
		return 0;
	}
	for(int i=1;i<=n;i++) printf("%d ",m[i]);
	puts("");
	cout<<m[2]<<" "<<m[1]<<" "<<m[3]<<" ";
	for(int i=4;i<=n-2;i++) cout<<m[i]<<" ";
	cout<<m[n]<<" "<<m[n-1]<<endl;
	return 0;
}
