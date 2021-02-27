#include <bits/stdc++.h>
using namespace std;
const int maxn=2e4+300;
typedef pair<int,int> P;

#define mid ((l+r)>>1)
#define ls ((o<<1))
#define rs ((o<<1)|1)
int val[maxn];
int x[maxn];
void change(int o,int l,int r,int p,int c){
	if(r-l==1){
		x[o]=l;
		val[o]+=c;
		return;
	}
	if(p>=mid) change(rs,mid,r,p,c);
	else change(ls,l,mid,p,c);
	if(val[ls]<val[rs]){
		val[o]=val[rs];
		x[o]=x[rs];
	}else{
		val[o]=val[ls];
		x[o]=x[ls];
	}
}
int n;
int a[maxn];
int ans[maxn];
int main(){
	freopen("./in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			change(1,1,n+1,a[j],1);
			ans[x[1]]++;
		}
		memset(val,0,sizeof val);
	}
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
