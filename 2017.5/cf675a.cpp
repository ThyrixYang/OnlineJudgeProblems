#include <bits/stdc++.h>

using namespace std;

long long a,b,c;
int main(){
	freopen("./in","r",stdin);
	cin>>a>>b>>c;
	if(c==0){
		if(a==b) puts("YES");
		else puts("NO");
		return 0;
	}
	if((b-a)%c==0&&(b-a)*c>=0) puts("YES");
	else puts("NO");
	return 0;
}
