#include <bits/stdc++.h> 
using namespace std;
typedef long long ll;

void kmp_pre(int x[],int m,int next[]){
	int i,j;
	j=next[0]=-1;
	i=0;
	while(i<m){
		while(-1!=j && x[i]!=x[j])j=next[j];
		next[++i]=++j;
	}
}
const int MAXN=1e6+30000;
int phi[MAXN];
int pri[MAXN];
bool VIS[MAXN];
void getEular(){
	for(int i=2;i<MAXN;i++){
		if(!VIS[i]) pri[++pri[0]]=i,phi[i]=i-1;
		for(int j=1;j<=pri[0]&&i*pri[j]<MAXN;j++){
			VIS[i*pri[j]]=1;
			if(i%pri[j]==0){
				phi[i*pri[j]]=phi[i]*pri[j];
				break;
			}else{
				phi[i*pri[j]]=phi[i]*(pri[j]-1);
			}
		}
	}
}
const int maxn=1e6+3000;
const ll mod=1e8+7;
const int ang=360000;
int S,P;
int a[maxn];
int b[maxn];
ll qpow(ll a,ll p){
	ll ans=1;
	while(p>0){
		if(p&1) ans=ans*a%mod;
		a=a*a%mod;p>>=1;
	}
	return ans;
}
ll inv(ll a){
	return qpow(a,mod-2);
}
int f[maxn];
int main(){
	freopen("/home/slyfc/vimFile/in","r",stdin);
	getEular();
	while(scanf("%d%d",&S,&P)){
		if(S==-1&&P==-1) break;
		for(int i=0;i<P;i++)
			scanf("%d",&a[i]);
		sort(a,a+P);
		for(int i=0;i<P-1;i++) b[i]=a[i+1]-a[i];
		b[P-1]=a[0]+ang-a[P-1];
		kmp_pre(b,P,f);
		int x=f[P];
		int cnt=1;
		ll ans=qpow(S,P);
		if(x!=0&&P%(P-x)==0){
			int len=P-x;
			P/=len;
			int d=2;
			while(d*d<=P){
				if(P%d==0){
					ans=(ans+qpow(S,len*d)*phi[P/d]%mod)%mod,cnt+=phi[P/d];
					if(d*d!=P){
						ans=(ans+qpow(S,len*P/d)*phi[d]%mod)%mod,cnt+=phi[d];
					}
				}
				d++;
			}
			ans=(ans+qpow(S,len)*phi[P]%mod)%mod,cnt+=phi[P];
		}
		ans=(ans*inv(cnt))%mod;
		printf("%d\n",(int)ans);
	}
	return 0;
}
