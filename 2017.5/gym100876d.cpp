#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define se second
#define fs first
map<ll,ll> M;
ll A,B;
ll get(ll x){
	if(x<=0) return 0;
	if(x<=min(A,B)) return 1;
	if(x-B<=0) return 1;
	map<ll,ll>::iterator it=M.find(x);
	if(it!=M.end()) return it->se;
	return M[x]=get(x-A)+get(x-B);
}
const double eps=1e-8;
double a,b,x;
int main(){
///	freopen("/home/cwind/vimFile/in","r",stdin);
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	cin>>a>>b>>x;
	A=a*1e5+eps,B=b*1e5+eps;
	if(A>B) swap(A,B);
	ll X=x*1e5+eps;
	cout<<get(X)<<endl;
	return 0;
}
