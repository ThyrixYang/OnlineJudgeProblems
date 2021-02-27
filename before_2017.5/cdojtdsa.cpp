#include <bits/stdc++.h>

using namespace std;

const int maxn=4e5;
long long val[maxn];
void update(int o,int p,int x,int l,int r){
	if(r-l==1){
		val[o]+=x;
		return;
	}
	int mid=(r+l)/2;
	if(p<mid) update(o<<1,p,x,l,mid);
	else update((o<<1)|1,p,x,mid,r);
	val[o]=max(val[o<<1],val[(o<<1)|1]);
}
long long query(int o,int a,int b,int l,int r){
	if(a>=r||b<=l) return 0;
	if(l>=a&&r<=b) return val[o];
	return max(query(o<<1,a,b,l,(l+r)/2),query((o<<1)|1,a,b,(l+r)>>1,r));
}
int main(){
	freopen("./in","r",stdin);
	int n,q;
	scanf("%d%d",&n,&q);
	while(q--){
		int t;
		scanf("%d",&t);
		if(t==1){
			int p,x;
			scanf("%d%d",&p,&x);
			update(1,p,x,1,n+1);
		}else{
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",query(1,l,r+1,1,n+1));
		}
	}
	return 0;
}
