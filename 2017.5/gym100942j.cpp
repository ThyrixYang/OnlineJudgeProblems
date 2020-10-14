#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> P;
#define fs first
#define se second
set<P> S;
int n;
ll p,st;
ll findPos(ll x){
	set<P>::iterator it=S.lower_bound(P(x,0));
	if(it->fs>x) it--;
	if(it->se>=x){
		ll s=it->fs;
		st=it->se;
		p+=it->se-it->fs;
		S.erase(it);
		return s;
	}
	return st=x;
}
void out(){
	set<P>::iterator it=S.begin();
	for(;it!=S.end();it++){
		cout<<it->fs<<" "<<it->se<<endl;
	}
	puts("---------");
}
int main(){
	freopen("/home/cwind/vimFile/in","r",stdin);
	S.insert(P(1e18,1e18));
	S.insert(P(-1,-1));
	cin>>n;
	while(n--){
		ll x;
		scanf("%lld",&x);
		if(x>0){
			scanf("%lld",&p);
			x=findPos(x);
			set<P>::iterator it=S.upper_bound(P(x,0));
			ll e=it->fs;
			if(e>x+p){
				printf("%lld %lld\n",st,x+p-1);
				S.insert(P(x,x+p));
			}else{
				printf("%lld %lld\n",st,e-1);
				e=it->se;
				S.erase(it);
				S.insert(P(x,e));
			}
		}else{
			x=-x;
			set<P>::iterator it=S.lower_bound(P(x,0));
			if(it->fs>x) it--;
			if(it->se<=x) continue;
			ll s=it->fs,t=it->se;
			S.erase(it);
			if(t-s==1) continue;
			if(s==x) S.insert(P(x+1,t));
			else if(t-1==x) S.insert(P(s,t-1));
			else S.insert(P(s,x)),S.insert(P(x+1,t));
		}
	}
	return 0;
}

