#include <bits/stdc++.h>

using namespace std;

const int maxn=105;
int n,k;
int fa[maxn],d[maxn],c[maxn];
int main(){
	freopen("./in","r",stdin);
	while(cin>>n>>k){
		memset(d,0,sizeof d);
		memset(c,0,sizeof c);
		for(int i=1;i<=n-1;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			d[x]++;
			fa[y]=x;
		}
		queue<int> Q;
		for(int i=1;i<=n;i++){
			if(d[i]==0) Q.push(i);
		}
		int cnt=0;
		while(!Q.empty()){
			int v=Q.front();
			Q.pop();
			if(c[v]==k) cnt++;
			c[fa[v]]+=c[v]+1;
			if(--d[fa[v]]==0) Q.push(fa[v]);
		}
		cout<<cnt<<endl;
	}
	return 0;
}
