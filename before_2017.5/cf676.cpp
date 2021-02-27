#include <bits/stdc++.h>

using namespace std;

const double eps=1e-6;
int n,t;
double val[20][20];
int main(){
	freopen("./in","r",stdin);
	cin>>n>>t;
	while(t--){
		val[1][1]+=100;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=i;j++){
				if(val[i][j]<100) continue;
				double x=val[i][j]-100;
				val[i][j]=100;
				val[i+1][j]+=x/2,val[i+1][j+1]+=x/2;
			}
		}
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			if(fabs(val[i][j]-100)<eps) cnt++;
		}
	}
	cout<<cnt<<endl;
	return 0;
}
