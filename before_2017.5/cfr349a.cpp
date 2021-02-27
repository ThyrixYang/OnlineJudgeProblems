#include <bits/stdc++.h>

using namespace std;

const int maxn=2e5;
char s[maxn];
set<string> out;
int len;
bool dp[maxn][2];
bool cmp(int s1,int s2,int x){
	for(int i=0;i<x;i++){
		if(s[s1+i]!=s[s2+i]) return 0;
	}
	return 1;
}
string f(int st,int x){
	string ans;
	for(int i=st;i<st+x;i++)
		ans+=s[i];
	return ans;
}
int main(){
	freopen("./in","r",stdin);
	scanf("%s",s);
	len=strlen(s);
	memset(dp,0,sizeof dp);
	dp[len-2][0]=1;
	dp[len-3][1]=1;
	for(int i=len-4;i>=0;i--){
		dp[i][0]|=dp[i+2][1];
		dp[i][1]|=dp[i+3][0];
		if(!cmp(i,i+2,2)) dp[i][0]|=dp[i+2][0];
		if(!cmp(i,i+3,3)) dp[i][1]|=dp[i+3][1];
	}
	for(int i=len-2;i>4;i--){
		if(dp[i][0]) out.insert(f(i,2));
		if(dp[i][1]) out.insert(f(i,3));
	}
	cout<<out.size()<<endl;
	set<string>::iterator it=out.begin();
	for(;it!=out.end();){
		cout<<(*it)<<endl;
		it++;
	}
	return 0;
}
