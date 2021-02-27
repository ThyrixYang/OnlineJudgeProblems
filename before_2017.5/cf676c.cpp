#include <bits/stdc++.h>

using namespace std;

const int maxn=1e6;
int n,k;
char s[maxn];
int main(){
	freopen("./in","r",stdin);
	cin>>n>>k;
	scanf("%s",s);
	int ans=0;
	int j=0,cnt=0;
	for(int i=0;i<n;i++){
		while(j<n&&cnt<k){
			if(s[j]=='a') cnt++;
			j++;
		}
		while(j<n&&s[j]=='b') j++;
		cnt-=(s[i]=='a');
		ans=max(ans,j-i);
	}
	j=0,cnt=0;
	for(int i=0;i<n;i++){
		while(j<n&&cnt<k){
			if(s[j]=='b') cnt++;
			j++;
		}
		while(j<n&&s[j]=='a') j++;
		cnt-=(s[i]=='b');
		ans=max(ans,j-i);
	}
	cout<<ans<<endl;
	
	return 0;
}
