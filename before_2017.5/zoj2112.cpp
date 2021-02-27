#include <bits/stdc++.h>

using namespace std;

const int maxb=16;
const int maxn=(1<<(maxb+1));
const int maxo=2400000;
int dic[maxn],dh;
int n,m;

int ls[maxo],rs[maxo],val[maxo];
int root[maxn];
int sz;

#define mi (l+((r-l)>>1))
inline void cp(int o,int oo){
	ls[o]=ls[oo],rs[o]=rs[oo],val[o]=val[oo];
}
void change(int &o,int l,int r,int p,int x){
	cp(++sz,o);
	o=sz;
	val[o]+=x;
	if(r-l==1) return;
	if(p<mi) change(ls[o],l,mi,p,x);
	else change(rs[o],mi,r,p,x);
}
int countLess(int o,int l,int r,int p){
	if(p<l) return 0;
	if(p+1>=r) return val[o];
	if(mi>p) return countLess(ls[o],l,mi,p);
	int ans=val[ls[o]];
	if(mi<=p) ans+=countLess(rs[o],mi,r,p);
	return ans;
}
int bit[maxn];
void update(int p,int x,int t){
	while(p<maxn) change(bit[p],1,n+1,x,t),p+=p&-p;
}
int count(int o,int a,int b,int l,int r){
	if(l>=b||r<=a) return 0;
	if(l>=a&&r<=b) return val[o];
	return count(ls[o],a,b,l,mi)+count(rs[o],a,b,mi,r);
}
int find(int left,int right,int k){
	int cnt=0,p=0;
	for(int i=maxb;i>=0;i--){
		p+=(1<<i);
		int c=countLess(root[right],0,maxn,p);
		c-=countLess(root[left-1],0,maxn,p);
		int cb=count(bit[p],left,right+1,1,n+1);
		if(c+cb+cnt>=k) p-=(1<<i);
		else cnt+=cb;
	}
	return p;
}
char s[5];
struct qu{
	int t,i,j,k;
	void in(){
		scanf("%s",s);
		if(s[0]=='Q') t=1,scanf("%d%d%d",&i,&j,&k);
		else t=2,scanf("%d%d",&i,&j),dic[dh++]=j;
	}
}Q[maxn];
int sc[maxn];
#define idx(x) (lower_bound(dic,dic+dh,x)-dic+1)
int TT;
void init(){
	sz=root[0]=0;
	dh=0;
	memset(bit,0,sizeof bit);
}
int main(){
	freopen("./in","r",stdin);
	cin>>TT;
	while(TT--){
		scanf("%d%d",&n,&m);
		init();
		for(int i=1;i<=n;i++) scanf("%d",&sc[i]),dic[dh++]=sc[i];
		for(int i=0;i<m;i++) Q[i].in();
		sort(dic,dic+dh);
		dh=unique(dic,dic+dh)-dic;
		for(int i=1;i<=n;i++){
			root[i]=root[i-1];
			change(root[i],0,maxn,idx(sc[i]),1);
		}
		for(int i=0;i<m;i++){
			if(Q[i].t==2){
				update(idx(Q[i].j),Q[i].i,1);
				update(idx(sc[Q[i].i]),Q[i].i,-1);
				sc[Q[i].i]=Q[i].j;
			}else{
				printf("%d\n",dic[find(Q[i].i,Q[i].j,Q[i].k)]);
			}
		}
	}
	return 0;
}
