#include<string>
#include<cstring>
#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;


const int maxn=1e5;
int ls[maxn],rs[maxn],par[maxn],val[maxn];
char lab[maxn][100];
int pri[maxn];
int id[maxn];
int n;
int R,sz,root;
void insert(int x){
	if(R==0){
		root=R=++sz;
		val[sz]=x;
		ls[sz]=rs[sz]=0;
		return;
	}
	val[++sz]=x;
	ls[sz]=rs[sz]=0;
	int last=0;
	while(R!=0&&pri[val[R]]<pri[x]){
		last=R;
		R=par[R];
	}
	ls[sz]=last;
	par[sz]=R;
	rs[R]=sz;
	if(R==0) root=sz;
	R=sz;
}
bool cmp(int a,int b){
	return strcmp(lab[a],lab[b])<0;
}
char s[maxn];
void out(int v){
	if(v==0) return;
	printf("(");
	out(ls[v]);
	printf("%s",lab[val[v]]);
	printf("/%d",pri[val[v]]);
	out(rs[v]);
	printf(")");
}
int main(){
	freopen("./in","r",stdin);
	while(scanf("%d",&n)){
		if(n==0) break;
		root=R=sz=0;
		for(int i=0;i<n;i++){
			id[i]=i;
			scanf("%s",s);
			int len=strlen(s);
			int p=0;
			for(;p<len;p++) if(s[p]=='/') break;
			s[p]=0;
			memcpy(lab[i],s,sizeof(char)*(p+1));
			sscanf(s+p+1,"%d",&pri[i]);
		}
		sort(id,id+n,cmp);
		for(int i=0;i<n;i++) insert(id[i]);
		out(root);
		puts("");
	}
	return 0;
}
