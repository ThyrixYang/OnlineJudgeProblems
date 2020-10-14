#include <bits/stdc++.h>

using namespace std;
const int MAXN=100000;
char s[MAXN];
int sa[MAXN],t[MAXN],t2[MAXN],c[MAXN],n;
void build_sa(int m=300){//m为最大字符值+1
	int i,*x=t,*y=t2;
	for(i=0;i<m;i++) c[i]=0;
	for(i=0;i<n;i++) c[x[i]=s[i]]++;
	for(i=1;i<m;i++) c[i]+=c[i-1];
	for(i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
	for(int k=1;k<=n;k<<=1){
		int p=0;
		for(i=n-k;i<n;i++) y[p++]=i;
		for(i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
		for(i=0;i<m;i++) c[i]=0;
		for(i=0;i<n;i++) c[x[y[i]]]++;
		for(i=0;i<m;i++) c[i]+=c[i-1];
		for(i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=1;x[sa[0]]=0;
		for(i=1;i<n;i++)
			x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
		if(p>=n) break;
		m=p;
	}
}
int rank[MAXN],height[MAXN];
void getHeight(){
	int i,j,k=0;
	for(i=0;i<n;i++) rank[sa[i]]=i;
	for(i=0;i<n-1;i++){
		if(k) k--;
		j=sa[rank[i]-1];
		while(s[i+k]==s[j+k]) k++;
		height[rank[i]]=k;
	}
}
int T;
int main(){
	freopen("./in","r",stdin);
	cin>>T;
	while(T--){
		scanf("%s",s);
		n=strlen(s);
		s[n++] = 0;
		build_sa();
		getHeight();
		int ans = 0;
		for(int i = 1; i < n; i++) {
			ans -= height[i];
			ans += n - 1 - sa[i];
		}
		printf("%d\n",ans);
	}
	return 0;
}
