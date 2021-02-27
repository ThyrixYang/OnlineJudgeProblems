#include <bits/stdc++.h>

using namespace std;

#define INF (0x3f3f3f3f)
const int maxn=2e5;
int n,a[maxn];
int sgn(int x){
	if(x%2) return 1;
	else return -1;
}
vector<int> pos;
int ss;
int check(int x,int y){
	if(x==y) return 0;
	for(int i=0;i<ss;i++){
		if((x<pos[i]||x>pos[i]+1)&&(y<pos[i]||y>pos[i]+1)) return 0;
	}
	if(x>y) swap(x,y);
	if(x==y-1){
		return a[x-1]*sgn(x-1)<a[y]*sgn(x-1)&&
			   a[y]*sgn(x)<a[x]*sgn(x)&&
			   a[x]*sgn(y)<a[y+1]*sgn(y);
	}
	return a[x-1]*sgn(x-1)<a[y]*sgn(x-1)&&
		   a[y]*sgn(x)<a[x+1]*sgn(x)&&
		   a[y-1]*sgn(y-1)<a[x]*sgn(y-1)&&
		   a[x]*sgn(y)<a[y+1]*sgn(y);
}
typedef pair<int,int> P;
set<P> S;
#define pb push_back
int main(){
	freopen("./in","r",stdin);
	cin>>n;
	a[0]=INF;
	if(n%2) a[n+1]=INF;
	else a[n+1]=-INF;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		if(!(sgn(i)*a[i]<sgn(i)*a[i+1])) pos.pb(i);
	ss=pos.size();
	if(ss>4){
		puts("0");
		return 0;
	}
	for(int i=0;i<ss;i++) pos.pb(pos[i]+1);
	int sz=pos.size();
	for(int i=0;i<sz;i++){
		int x=pos[i],y=pos[i]+1;
		for(int i=1;i<=n;i++) if(check(x,i)) S.insert(P(x,i)),S.insert(P(i,x));
		for(int i=1;i<=n;i++) if(check(y,i)) S.insert(P(y,i)),S.insert(P(i,y));
	}
	cout<<S.size()/2<<endl;
	return 0;
}
