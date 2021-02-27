#include <bits/stdc++.h>

using namespace std;

typedef unsigned int ui;

ui n,p,q,ans=0;
ui C[200];
ui mul[200],di[200];
void getC(ui k){
	for(int i=0;i<k;i++) mul[i]=n-i;
	for(int i=1;i<=k;i++) di[i]=i;
	for(int i=0;i<k;i++){
		for(int j=1;j<=k;j++){
			ui g=__gcd(mul[i],di[j]);
			if(g>1) mul[i]/=g,di[j]/=g;
		}
	}
	C[k]=1;
	for(int i=0;i<k;i++) C[k]*=mul[i];
}
int main(){
	freopen("./in","r",stdin);
	cin>>n>>p>>q;
	p=min(n-1,p);
	for(int i=0;i<=p;i++) getC(i);
	for(int i=1;i<=q;i++){
		ui tmp=0,ii=i;
		for(int j=0;j<=p;j++){
			tmp+=C[j]*ii;
			ii*=i;
		}
		ans^=tmp;
	}
	cout<<ans<<endl;
	return 0;
}
