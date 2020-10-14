#include <bits/stdc++.h>

using namespace std;

int l,n,k;
int main(){
	freopen("/home/cwind/vimFile/in","r",stdin);
	cin>>l>>n>>k;
	if(k==1){
		puts("0");
		return 0;
	}
	if(k==2){
		if(l==1&&n>1) puts("1");
		else puts("0");
		return 0;
	}
	for(int i=1;i<=l;i++){
		if(n==0) break;
		if(n==1){
			n=0;
			break;
		}
		if(n==2){
			n=1;
			continue;
		}
		if(n>=k&&n<=k+2){
			n=k-1;
			continue;
		}
		if(n<k){
			n-=l-i+1;
			if(n<0) n=0;
			break;
		}
		int cnt=n/k;
		int rem=n%k;
		if(rem>=2) n-=cnt*2+1;
		else n=k-1+(cnt-1)*(k-2);
	}
	cout<<n<<endl;
	return 0;
}
