#include<bits/stdc++.h>

using namespace std;

int n,m,q;
int a[105][105];
int ans[105][105];
void sr(int r){
	int s=a[r][0];
	for(int i=0;i<m;i++) a[r][i]=a[r][i+1];
	a[r][m-1]=s;
}
void sc(int c){
	int s=a[0][c];
	for(int i=0;i<n;i++) a[i][c]=a[i+1][c];
	a[n-1][c]=s;
}
int main(){
	freopen("./in","r",stdin);
	cin>>n>>m>>q;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			a[i][j]=i*m+j;
	while(q--){
		int t;
		scanf("%d",&t);
		if(t==1){
			int r;
			scanf("%d",&r);
			r--;
			sr(r);
		}else if(t==2){
			int c;
			scanf("%d",&c);
			c--;
			sc(c);
		}else{
			int r,c,x;
			scanf("%d%d%d",&r,&c,&x);
			r--,c--;
			ans[a[r][c]/m][a[r][c]%m]=x;
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cout<<ans[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
