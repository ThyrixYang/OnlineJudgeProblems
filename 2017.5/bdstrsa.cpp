
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=1e6;
const int mod=9973;
int qpow(int a,int p){
	int ans=1;
	while(p>0){
		if(p&1) ans=ans*a%mod;
		a=a*a%mod;p>>=1;
	}
	return ans;
}
char s[maxn];
int h[maxn];
int n;
int main(){
	freopen("./in","r",stdin);
	while(scanf("%d",&n)!=EOF){
		scanf("%s",s);
		int len=strlen(s);
		h[0]=1;
		for(int i=0;i<len;i++){
			h[i+1]=h[i]*(s[i]-28)%mod;
		}
		for(int i=0;i<n;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			printf("%d\n",h[b]*qpow(h[a-1],mod-2)%mod);
		}
	}
	return 0;
}
