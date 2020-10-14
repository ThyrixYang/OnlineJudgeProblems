#include <bits/stdc++.h>

using namespace std;

const int maxn=1e6;
struct EDGE{
	int from,to,c,next;
	EDGE(int from=0,int to=0,int c=0,int next=0):from(from),to(to),c(c),next(next){}
}E[maxn];
int eh=0;
int head[maxn];
void addedge(int from,int to,int c){
	E[eh]=EDGE(from,to,c,head[from]);
	head[from]=eh++;
}
int n,m;
vector<int> ans[2];
int col[maxn];
int now;
int cnt[2];
vector<int> tmp[2];
#define pb push_back
bool dfs(int v){
	for(int i=head[v];i!=-1;i=E[i].next){
		EDGE &e=E[i];
		if(col[e.to]!=-1){
			if((now==e.c)!=(col[v]==col[e.to])) return 0;
		}else{
			if(now==e.c) col[e.to]=col[v];
			else col[e.to]=col[v]^1;
			cnt[col[e.to]]++;
			tmp[col[e.to]].pb(e.to);
			dfs(e.to);
		}
	}
	return 1;
}
bool color(int c){
	now=c;
	memset(col,-1,sizeof col);
	for(int i=1;i<=n;i++){
		if(col[i]==-1){
			col[i]=0;
			cnt[0]=1,cnt[1]=0;
			tmp[0].clear();tmp[1].clear();
			tmp[0].pb(i);
			if(!dfs(i)) {
				return 0;
			}
			else{
				if(cnt[0]<cnt[1]){
					while(!tmp[0].empty()){
						ans[c].pb(tmp[0].back());
						tmp[0].pop_back();
					}
				}else{
					while(!tmp[1].empty()){
						ans[c].pb(tmp[1].back());
						tmp[1].pop_back();
					}
				}
			}
		}
	}
	return 1;
}
int main(){
	freopen("./in","r",stdin);
	memset(head,-1,sizeof head);
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int x,y;
		char z;
		scanf("%d %d %c",&x,&y,&z);
		if(z=='R') z=1;
		else z=0;
		addedge(x,y,z);
		addedge(y,x,z);
	}
	int f0=color(0);
	int f1=color(1);
	int out=-1;
	if(f1&&f0){
		if(ans[0].size()<ans[1].size()) out=0;
		else out=1;
	}else if(f1){
		out=1;
	}else if(f0){
		out=0;
	}else{
		puts("-1");
		return 0;
	}
	cout<<ans[out].size()<<endl;
	for(int i=0;i<ans[out].size();i++) printf("%d ",ans[out][i]);
	return 0;
}
