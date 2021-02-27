#include <bits/stdc++.h>

using namespace std;
const int MAXN=6e5;
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
// height[i] = sa[i-1] 与 sa[i] 的最长公共前缀
int rank[MAXN],height[MAXN];
void getHeight(){
	int i,j,k=0;
	for(i=0;i<n;i++) rank[sa[i]]=i;
	for(i=0;i<n-1;i++){//注意最后的一位是0，不计算height
		if(k) k--;
		j=sa[rank[i]-1];
		while(s[i+k]==s[j+k]) k++;
		height[rank[i]]=k;
	}
}
int cnt[MAXN];
vector<int> vi[MAXN];
int r[MAXN];
int main(){
	freopen("./in","r",stdin);
	cin>>n;
	scanf("%s",s);
	s[n++]=0;
	build_sa();
	getHeight();
	n--;
	for(int i=1;i<=n;i++) r[sa[i]]=sa[i]+height[i]+1;
	for(int i=0;i<=n;i++){
		cout<<i<<" "<<sa[i]<<" "<<height[i]<<endl;
	}
	int c=n;
	cnt[0]=c;
	for(int i=1;i<=n;i++){
		if(s[i-1]=='(') cnt[i]=++c;
		else cnt[i]=--c;
	}
	long long ans=0;
	vi[cnt[n]].push_back(-n);
	for(int i=n-1;i>=0;i--){
		//cout<<r[i]<<endl;
		int ed=n;
		int c=cnt[i];
		if(vi[c-1].size()) ed=-vi[c-1].back();
		int add=lower_bound(vi[c].begin(),vi[c].end(),-r[i]+1)-
				lower_bound(vi[c].begin(),vi[c].end(),-ed);
		vi[c].push_back(-i);
		//cout<<r[i]<<" "<<ed<<endl;
		cout<<i<<" "<<r[i]<<" "<<ed<<endl;
		if(ed<=r[i]) continue;
		ans+=add;
		cout<<i<<" "<<ans<<endl;
	}
	cout<<ans<<endl;
	return 0;
}
