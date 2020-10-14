#include <bits/stdc++.h>

using namespace std;

int T;
char s[1000];
map<vector<int>,int> M;
void init(){
	for(int x=1989;x<=30000;x++){
		vector<int> tmp;
		int y=x;
		tmp.push_back(y%10);
		y/=10;
		for(;;){
			if(M.find(tmp)==M.end()){
				M[tmp]=x;
				break;
			}
			if(y==0) break;
			tmp.push_back(y%10);
			y/=10;
		}
	}
}
long long p10[20];
int f(long long x,int t){
	x/=p10[t];
	return x%10;
}
int main(){
	freopen("./in","r",stdin);
	p10[0]=1;
	for(int i=1;i<20;i++) p10[i]=p10[i-1]*10;
	init();
	cin>>T;
	while(T--){
		scanf("%s",s);
		int len=strlen(s);
		vector<int> a,b;
		for(int i=len-1;i>3;i--) a.push_back(s[i]-'0');
		b.push_back(s[len-1]-'0');
		long long last=M[b];
		for(int i=0;i<a.size();i++){
			if(i!=0) last+=p10[i];
			while(f(last,i)!=a[i]) last+=p10[i];

		}
		cout<<last<<endl;
	}
	return 0;
}
