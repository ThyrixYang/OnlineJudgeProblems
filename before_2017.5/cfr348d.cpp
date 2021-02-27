#include <bits/stdc++.h>

using namespace std;

const int maxn=1e5+3000;
int n;
int a[maxn],t[maxn],x[maxn];
int ans[maxn];
int tmp[maxn];
int id[maxn];
map<int,int> M;
void solve(int l,int r){
	if(r-l==1) return;
	int mid=(r+l)>>1;
	solve(l,mid);
	solve(mid,r);
	M.clear();
	int pl=l,pr=mid;
	int pt=l;
	while(pl<mid||pr<r){
		if(pr==r||pl<mid&&t[id[pl]]<=t[id[pr]]){
			if(a[id[pl]]==1) ++M[x[id[pl]]];
			else if(a[id[pl]]==2) --M[x[id[pl]]];
			tmp[pt++]=id[pl++];
		}else{
			if(a[id[pr]]==3) ans[id[pr]]+=M[x[id[pr]]];
			tmp[pt++]=id[pr++];
		}
	}
	memcpy(id+l,tmp+l,sizeof(int)*(r-l));
}
int main(){
	freopen("./in","r",stdin);
	cin>>n;
	for(int i=0;i<n;i++){
		scanf("%d%d%d",&a[i],&t[i],&x[i]);
		id[i]=i;
	}
	solve(0,n);
	for(int i=0;i<n;i++)
		if(a[i]==3) printf("%d\n",ans[i]);
	return 0;
}
