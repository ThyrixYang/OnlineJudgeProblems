#include <bits/stdc++.h>

using namespace std;

#define se second
#define fs first
typedef long long ll;
typedef pair<int,int> P;

const int maxn=2e6;
int n;
int op[maxn][2];
char s[200];
vector<P> add[maxn];
map<int,int> M;
int cnt=0;
int main(){
	freopen("./in","r",stdin);
	cin>>n;
	for(int i=0;i<n;i++){
		scanf("%s",s);
		if(s[0]=='i'){
			op[i][0]=0;
		}else if(s[0]=='g'){
			op[i][0]=1;
		}else{
			op[i][0]=2;
		}
		if(op[i][0]!=2) scanf("%d",&op[i][1]);
		if(op[i][0]==0) ++M[op[i][1]];
		else if(op[i][0]==1){
			map<int,int>::iterator it=M.begin();
			while(it!=M.end()){
				if(it->fs>=op[i][1]) break;
				for(int j=0;j<it->se;j++) add[i].push_back(P(2,0)),cnt++;
				M.erase(it);
				it=M.begin();
			}
			if(it==M.end()||it->fs>op[i][1]) {
				add[i].push_back(P(0,op[i][1])),cnt++;
				++M[op[i][1]];
			}
		}else{
			if(M.empty()) add[i].push_back(P(0,0)),cnt++;
			else{
				map<int,int>::iterator it=M.begin();
				if(--it->se==0) M.erase(it);
			}
		}
	}
	/*
	for(int i=n-1;i>=0;i--){
		if(op[i][0]==0){
			map<int,int>::iterator it=M.find(op[i][1]);
			if(it==M.end()){
				add[i+1].push_back(P(2,0));
				cnt++;
			}
			if(--it->se==0){
				M.erase(it);
			}
		}else if(op[i][0]==1){
			if(M.empty()){
				add[i].push_back(P(0,op[i][1]));
				cnt++;
			}else{
				map<int,int>::iterator it=M.begin();
				while(it!=M.end()){
					if(it->fs>=op[i][1]) break;
					for(int j=0;j<it->se;j++) add[i].push_back(P(2,0)),cnt++;
					it++;
				}
				if(it==M.end()||it->fs>op[i][1]){
					add[i].push_back(P(0,op[i][1]));
					cnt++;
				}
			}
		}else{
			if(M.empty()) add[i].push_back(P(2,1));
		}
	}*/
	cout<<n+cnt<<endl;
	for(int i=0;i<=n;i++){
		for(int j=0;j<add[i].size();j++){
			P x=add[i][j];
			if(x.fs==0) printf("insert ");
			else if(x.fs==1) printf("getMin ");
			else printf("removeMin\n");
			if(x.fs!=2) printf("%d\n",x.se);
		}
		if(i==n) break;
		if(op[i][0]==0) printf("insert ");
		else if(op[i][0]==1) printf("getMin ");
		else printf("removeMin\n");
		if(op[i][0]!=2) printf("%d\n",op[i][1]);
	}
	return 0;
}
