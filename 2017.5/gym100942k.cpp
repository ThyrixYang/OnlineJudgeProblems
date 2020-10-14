#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
const int maxn=1e5;
char a[maxn],b[maxn];
vector<pair<int,int> > ans;
int main(){
	freopen("/home/cwind/vimFile/in","r",stdin);
	scanf("%s%s",a,b);
	int len=strlen(a);
	for(int i=0;i<len;i++){
		if(a[i]!=b[i]){
			int cnt=0;
			int p=-1;
			for(int j=i;j<len;j++){
				cnt+=a[j]=='1';
				if(cnt%2==0&&a[j]==b[i]){
					p=j;
					break;
				}
			}
			if(p==-1){
				puts("NO");
				return 0;
			}
			reverse(a+i,a+p+1);
			ans.pb(mp(i,p));
		}
	}
	puts("YES");
	cout<<ans.size()<<endl;
	for(int i=0;i<ans.size();i++){
		printf("%d %d\n",ans[i].first+1,ans[i].second+1);
	}
	return 0;
}
