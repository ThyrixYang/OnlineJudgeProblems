#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<iostream>

using namespace std;

const int maxn=4e5;
int ch[maxn][2];
int val[maxn];
int T,cas=0;
int n,m,l;
int a[maxn];
int dp[maxn][11];
int ti[maxn][11];
int sz;
int sum[maxn];
int bs[40];
int timer=0;
void getb(int x){
	for(int i=30;i>=0;i--){
		bs[i]=x&1;
		x>>=1;
	}
	reverse(bs,bs+31);
}
void insert(int x){
	getb(x);
	int v=0;
	for(int i=0;i<=30;i++){
		if(ch[v][bs[i]]==0){
			ch[v][bs[i]]=++sz;
			memset(ch[sz],0,sizeof ch[sz]);
		}
		v=ch[v][bs[i]]
		val[v]++;
	}
}
void del(int x){
	getb(x);
	int v=0;
	for(int i=0;i<=30;i++){
		v=ch[v][bs[i]];
		val[v]--;
	}
}
void init_trie(){
	sz=0;
	memset(ch[0],0,sizeof ch[0]);
}
int check(int mid){
	init_trie();
	insert(0);
	for(int i=1;i<=n;i++){
		int ll=i-l-1;
		if(ll>=0) del(a[ll]);
		int f=0;
		getb(a[i]);
		int tol=0,p=(1<<30);
		int v=0;
		for(int i=0;i<=30;i++){
			if(bs[i]==0){
				
			}else{
				
			}
		}
	}
}
int main(){
	freopen("./in","r",stdin);
	cin>>T;
	while(T--){
		init();
		printf("Case #%d:\n",++cas);
		scanf("%d%d%d",&n,&m,&l);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++) sum[i]=sum[i-1]^a[i];

	}
	return 0;
}
