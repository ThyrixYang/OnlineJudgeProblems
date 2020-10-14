#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <utility>
using namespace std;

typedef long long ll;
#define INF (0x3f3f3f3f)
const int maxn=2000;
struct plat{
	ll l,r,h;
	ll minl,minr;
	bool operator < (const plat &C)const{
		return h>C.h;
	}
	void in(){
		cin>>l>>r>>h;
		if(l>r) swap(l,r);
		minl=minr=1e18;
	}
}a[maxn];
int T;
ll N,X,Y,MAX;
int main(){
	freopen("/home/slyfc/vimFile/in","r",stdin);
	cin>>T;
	while(T--){
		cin>>N>>X>>Y>>MAX;
		for(int i=0;i<N;i++) a[i].in();
		sort(a,a+N);
		ll ans=1e18;
		int f=1;
		for(int i=0;i<N;i++){
			if(X>=a[i].l&&X<=a[i].r&&Y-a[i].h<=MAX){
				f=0;
				a[i].minl=X-a[i].l;
				a[i].minr=a[i].r-X;
				break;
			}
		}
		if(f) ans=0;
		for(int i=0;i<N;i++){
			int near=-1;
			for(int j=i+1;j<N;j++){
				if(a[j].l<=a[i].l&&a[j].r>=a[i].l&&a[j].h<a[i].h){
					near=j;
					break;
				}
			}
			if(near==-1){
				if(a[i].h<=MAX) ans=min(ans,a[i].minl);
			}
			else if(a[i].h-a[near].h<=MAX){
				a[near].minl=min(a[near].minl,a[i].minl+a[i].l-a[near].l);
				a[near].minr=min(a[near].minr,a[i].minl+a[near].r-a[i].l);
			}
			near=-1;
			for(int j=i+1;j<N;j++){
				if(a[j].l<=a[i].r&&a[j].r>=a[i].r&&a[j].h<a[i].h){
					near=j;
					break;
				}
			}
			if(near==-1){
				if(a[i].h<=MAX) ans=min(ans,a[i].minr);
			}
			else if(a[i].h-a[near].h<=MAX){
				a[near].minl=min(a[near].minl,a[i].minr+a[i].r-a[near].l);
				a[near].minr=min(a[near].minr,a[i].minr+a[near].r-a[i].r);
			}
		}
		cout<<ans+Y<<endl;
	}
	return 0;
}
