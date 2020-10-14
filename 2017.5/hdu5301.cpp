#include <bits/stdc++.h>

using namespace std;


int n,m,x,y;
int cal(int n,int m,int x,int y){
	int c=min(n-x,(m+1)/2);
	int ans1=max(x,c);
	int ans2=max(max(x-1,max(y-1,m-y)),c);
	int ans3=max((m+1)/2,max(max(y-1,m-y),c));
	return min(ans3,min(ans1,ans2));
}
int main(){
	freopen("./in","r",stdin);
	while(scanf("%d%d%d%d",&n,&m,&x,&y)!=EOF){
		int ans=cal(n,m,x,y);
		ans=min(ans,cal(n,m,n-x+1,y));
		ans=min(ans,cal(n,m,x,m-y+1));
		ans=min(ans,cal(n,m,n-x+1,m-y+1));
		swap(n,m);swap(x,y);
		ans=min(ans,cal(n,m,x,y));
		ans=min(ans,cal(n,m,n-x+1,y));
		ans=min(ans,cal(n,m,x,m-y+1));
		ans=min(ans,cal(n,m,n-x+1,m-y+1));
		cout<<ans<<endl;
	}
	return 0;
}
