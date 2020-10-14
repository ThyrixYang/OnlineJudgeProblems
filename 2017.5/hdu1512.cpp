#include <bits/stdc++.h>

using namespace std;

//左偏树，大根堆
const int maxn=1e5+2000;
struct Node{
	int val,dist;
	int ls,rs;
}T[maxn];
//合并r1,r2,合并后根为r1;
int merge(int r1,int r2){
	if(T[r1].val<T[r2].val) swap(r1,r2);
	if(r1==0) return r2;
	if(r2==0) return r1;
	T[r1].rs=merge(T[r1].rs,r2);
	if(T[T[r1].rs].dist>T[T[r1].ls].dist) swap(T[r1].ls,T[r1].rs);
	T[r1].dist=T[T[r1].rs].dist+1;
	return r1;
}
void pop(int &root){
	T[root].val/=2;
	T[root].dist=0;
	int tr=merge(T[root].ls,T[root].rs);
	T[root].ls=T[root].rs=0;
	root=merge(tr,root);
}
int n,m;
int fa[maxn],root[maxn];
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
int main(){
	freopen("./in","r",stdin);
	T[0].dist=T[0].val=-1;
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<=n;i++){
			int x;
			scanf("%d",&x);
			fa[i]=i;
			root[i]=i;
			T[i].ls=T[i].rs=T[i].dist=0;
			T[i].val=x;
		}
		scanf("%d",&m);
		while(m--){
			int x,y;
			scanf("%d%d",&x,&y);
			if(find(x)==find(y)){
				puts("-1");
				continue;
			}
			int fx=find(x),fy=find(y);
			pop(root[fx]);pop(root[fy]);
			fa[fy]=fx;
			root[fx]=merge(root[fx],root[fy]);
			printf("%d\n",T[root[fx]].val);
		}
	}
	return 0;
}
