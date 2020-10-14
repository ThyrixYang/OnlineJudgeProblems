#include<iostream>
#include<cstdio>
#include<bitset>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

const int maxn=35005;
struct Point{
	int x[2];
	Point(int a=0,int b=0){x[0]=a,x[1]=b;}
	int& operator [] (const int &C){return x[C];}
	void in(){scanf("%d%d",&x[0],&x[1]);}
}p[maxn];
struct Node{
	int v;
	int s[2];
	Point Min,Max;
	bitset<maxn> b0;
	void up(Node &a){
		Min[0]=min(Min[0],a.Min[0]);
		Min[1]=min(Min[1],a.Min[1]);
		Max[0]=max(Max[0],a.Max[0]);
		Max[1]=max(Max[1],a.Max[1]);
	}
}T[maxn];
vector<int> G[maxn];
int d;
int id[maxn];
bool cmp(int a,int b){
	return p[a][d]<p[b][d];
}
int sz;
#define mi ((r+l)>>1)
#define ls T[o].s[0]
#define rs T[o].s[1]
int To[maxn];
void build(int &o,int l,int r,int w){
	if(l>=r) return;
	d=w;
	nth_element(id+l,id+mi,id+r,cmp);
	o=++sz;
	T[o].v=id[mi];
	To[id[mi]]=o;
	T[o].Max=T[o].Min=p[id[mi]];
	build(ls,l,mi,w^1);
	build(rs,mi+1,r,w^1);
	if(ls) T[o].up(T[ls]);
	if(rs) T[o].up(T[rs]);
}

#define sq(x) ((x)*(x))
Point qp;
int qid;
int R,A;
int diste1(Point &a,Point &b){
	return max(sq(a[0]-qp[0]),sq(b[0]-qp[0]))+max(sq(a[1]-qp[1]),sq(b[1]-qp[1]));
}
int distm1(Point &a,Point &b){
	return max(abs(a[0]-qp[0]),abs(b[0]-qp[0]))+max(abs(a[1]-qp[1]),abs(b[1]-qp[1]));
}
int sgn(int x){
	if(x>0) return 1;
	return 0;
}
int diste2(Point &a,Point &b){
	int d1=sgn((a[0]-qp[0])*(b[0]-qp[0]));
	int d2=sgn((a[1]-qp[1])*(b[1]-qp[1]));
	return min(sq(a[0]-qp[0]),sq(b[0]-qp[0]))*d1+min(sq(a[1]-qp[1]),sq(b[1]-qp[1]))*d2;
}
int distm2(Point &a,Point &b){
	int d1=sgn((a[0]-qp[0])*(b[0]-qp[0]));
	int d2=sgn((a[1]-qp[1])*(b[1]-qp[1]));
	return min(abs(a[0]-qp[0]),abs(b[0]-qp[0]))*d1+min(abs(a[1]-qp[1]),abs(b[1]-qp[1]))*d2;
}
void mark(int o){
	if(!o) return;
	if(diste1(T[o].Max,T[o].Min)<=R||distm1(T[o].Min,T[o].Max)<=A){
		T[o].b0[qid]=1;
		return;
	}
	if(diste2(T[o].Max,T[o].Min)>R&&distm2(T[o].Min,T[o].Max)>A) return;
	if(diste1(p[T[o].v],p[T[o].v])<=R||distm1(p[T[o].v],p[T[o].v])<=A) G[T[o].v].push_back(qid);
	mark(ls);
	mark(rs);
}
int belong[maxn];
vector<int> member[maxn];
bitset<maxn> tmp;
void push(int o){
	if(ls) T[ls].b0|=T[o].b0,push(ls);
	if(rs) T[rs].b0|=T[o].b0,push(rs);
}
int n,m,k;
int ri[maxn],ai[maxn],pi[maxn];
int root;
int main(){
	freopen("./in","r",stdin);
	cin>>n>>m>>k;
	for(int i=0;i<n;i++){
		p[i].in();
		id[i]=i;
		scanf("%d%d%d",&ri[i],&ai[i],&pi[i]);
		belong[i]=pi[i];
		member[pi[i]].push_back(i);
	}
	sz=0;
	build(root,0,n,0);
	for(int i=0;i<n;i++){
		qp=p[i];
		qid=i;
		R=sq(ri[i]);
		A=ai[i];
		mark(root);
	}
	push(root);
	double ans=0;
	for(int i=1;i<=k;i++){
		bitset<maxn> tmp;
		for(int j=0;j<member[i].size();j++){
			int v=member[i][j];
			tmp|=T[To[v]].b0;
			for(int x=0;x<G[v].size();x++) tmp[G[v][x]]=1;
		}
		for(int j=0;j<member[i].size();j++){
			tmp[member[i][j]]=0;
		}
		int cnt=tmp.count();
		ans+=pow((n-cnt*1.0)/n,m);
	}
	printf("%.5f\n",ans);
	return 0;
}
