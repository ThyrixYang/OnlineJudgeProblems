#include <bits/stdc++.h>

using namespace std;

long long a,b,c,d;
int T;
long long getans(long long n){
	return c*n-(a*n/b)*d;
}
int main(){
	freopen("./in","r",stdin);
	cin>>T;
	while(T--){
		scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
		if(a<=b){
			long long n=(b+a-1)/b;
			if(getans(n)<getans(1)) printf("%lld\n",n);
			else puts("1");
		}else{
			long long n=b/__gcd(a,b);
			printf("%lld\n",n);
		}
	}
	return 0;
}
