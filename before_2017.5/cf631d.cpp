#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
void kmp_pre(pair<char,ll> x[],int m,int next[]){
	int i,j;
	j=next[0]=-1;
	i=0;
	while(i<m){
		while(-1!=j && x[i]!=x[j])j=next[j];
		next[++i]=++j;
	}
}

const int maxn=3e5;
#define mp make_pair
#define fs first
#define se second
int n,m;
pair<char,ll> a[maxn],b[maxn];
int ah=0,bh=0;
int f[maxn];
int main(){
	freopen("./in","r",stdin);
	cin>>n>>m;
	for(int i=0;i<n;i++){
		char c;
		int l;
		scanf("%d-%c",&l,&c);
		if(ah>0&&a[ah-1].fs==c) a[ah-1].se+=l;
		else a[ah++]=mp(c,l);
	}
	for(int i=0;i<m;i++){
		char c;
		int l;
		scanf("%d-%c",&l,&c);
		if(bh>0&&b[bh-1].fs==c) b[bh-1].se+=l;
		else b[bh++]=mp(c,l);
	}
	ll cnt=0;
	if(bh==1){
		for(int i=0;i<ah;i++){
			if(a[i].fs==b[0].fs){
				if(a[i].se>=b[0].se) 
					cnt+=a[i].se-b[0].se+1;
			}
		}
		cout<<cnt<<endl;
		return 0;
	}
	kmp_pre(b,bh,f);
	int j=-1;
	for(int i=0;i<ah;i++){
		while(j!=-1&&b[j]!=a[i]) j=f[j];
		j++;
		if(j==0&&a[i].fs==b[0].fs&&a[i].se>=b[0].se) j=1;
		if(j==bh) cnt++;
		else if(j==bh-1&&a[i+1].fs==b[j].fs&&a[i+1].se>b[j].se) cnt++;
	}
	cout<<cnt<<endl;
	return 0;
}
