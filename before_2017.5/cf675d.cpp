#include <bits/stdc++.h>

using namespace std;

const int maxn=1e6;
map<int,int> ls,rs;
set<int> S;
int n;
int main(){
	freopen("./in","r",stdin);
	cin>>n;
	for(int i=0;i<n;i++){
		int x;
		scanf("%d",&x);
		if(i==0){
			S.insert(x);
			continue;
		}
		set<int>::iterator it=S.lower_bound(x);
		if(it==S.end()){
			it--;
			rs[*it]=x;
			printf("%d ",*it);
		}else{
			if(ls[*it]==0){
				ls[*it]=x;
				printf("%d ",*it);
			}else{
				it--;
				rs[*it]=x;
				printf("%d ",*it);
			}
		}
		S.insert(x);
	}
	return 0;
}
