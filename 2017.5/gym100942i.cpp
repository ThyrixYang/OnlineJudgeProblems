#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define se second
struct Node{
	int a[4];
	Node(){}
	Node(int *b){memcpy(a,b,sizeof a);}
	bool operator < (const Node &C)const{
		for(int i=0;i<4;i++){
			if(a[i]<C.a[i]) return 1;
			if(a[i]>C.a[i]) return 0;
		}
		return 0;
	}
	int dis(const Node &C)const{
		int ans=0;
		for(int i=0;i<4;i++) ans+=abs(a[i]-C.a[i]);
		return ans;
	}
};
priority_queue<pair<int,Node> > Q[16];
set<Node> S;
int n;
int b[4];
int main(){
	freopen("/home/cwind/vimFile/in","r",stdin);
	cin>>n;
	while(n--){
		int t;
		scanf("%d",&t);
		for(int i=0;i<4;i++) scanf("%d",&b[i]);
		if(t==1){
			S.insert(Node(b));
			for(int i=0;i<16;i++){
				int tmp=0;
				for(int j=0;j<4;j++){
					if((i>>j)&1) tmp+=b[j];
					else tmp-=b[j];
				}
				Q[i].push(mp(tmp,Node(b)));
			}
		}else if(t==2){ 
			S.erase(S.find(Node(b)));
		}else{
			Node nn(b);
			int ans=0;
			for(int i=0;i<16;i++){
				while(!Q[i].empty()){
					if(S.find(Q[i].top().se)==S.end()){
						Q[i].pop();
						continue;
					}
					ans=max(ans,nn.dis(Q[i].top().se));
					break;
				}
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
