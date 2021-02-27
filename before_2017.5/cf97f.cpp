#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> P;

#define fs first
#define se second
const int maxn=2e4;
int n;
P a[maxn];
set<P> S;
void solve(int l,int r){
	if(r-l==1) return;
	int mid=(r+l)>>1;
	solve(l,mid);
	solve(mid,r);
	int x=a[mid].fs;
	for(int i=l;i<r;i++){
		S.insert(P(x,a[i].se));
	}
}
int main(){
	freopen("/home/cwind/vimFile/in","r",stdin);
	cin>>n;
	for(int i=0;i<n;i++){
		scanf("%d%d",&a[i].fs,&a[i].se);
		S.insert(a[i]);
	}
	sort(a,a+n);
	solve(0,n);
	cout<<S.size()<<endl;
	set<P>::iterator it=S.begin();
	while(it!=S.end()){
		printf("%d %d\n",it->fs,it->se);
		it++;
	}
	return 0;
}
