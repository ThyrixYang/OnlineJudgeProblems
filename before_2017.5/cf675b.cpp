#include <bits/stdc++.h>

using namespace std;

long long a,b,c,d,n,x1,x2,x4,x5;
int in(int x){
	return x>=1&&x<=n;
}
int main(){
	freopen("./in","r",stdin);
	cin>>n>>a>>b>>c>>d;
	long long ans=0;
	for(x1=1;x1<=n;x1++){
		x2=x1+b-c;
		x5=a+x2-d;
		x4=x5+c-b;
		if(in(x2)&&in(x5)&&in(x4)) ans++;
	}
	cout<<ans*n<<endl;
	return 0;
}
