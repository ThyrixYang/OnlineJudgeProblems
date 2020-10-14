#include <bits/stdc++.h>

using namespace std;

#define fs first
#define se second
typedef pair<int,int> P;
const int maxn=10000;
int T,cas=0;
char a[maxn],b[maxn];
int as[maxn],bs[maxn];
int ah,bh;
int lena,lenb;
void dfsa(int p,int val){
	if(p==lena){
		as[ah++]=val;
		return;
	}
	if(a[p]!='?') dfsa(p+1,val*10+a[p]-'0');
	else{
		for(int i=0;i<10;i++)
			dfsa(p+1,val*10+i);
	}
}
void dfsb(int p,int val){
	if(p==lenb){
		bs[bh++]=val;
		return;
	}
	if(b[p]!='?') dfsb(p+1,val*10+b[p]-'0');
	else{
		for(int i=0;i<10;i++)
			dfsb(p+1,val*10+i);
	}
}
int getlen(int x){
	if(x==0) return 1;
	int len=0;
	for(;;){
		if(x==0) return len;
		x/=10;
		len++;
	}
}
int main(){
	freopen("./in","r",stdin);
	freopen("./out","w",stdout);
	cin>>T;
	while(T--){
		printf("Case #%d: ",++cas);
		scanf("%s%s",a,b);
		lena=strlen(a);
		lenb=strlen(b);
		ah=bh=0;
		dfsa(0,0);
		dfsb(0,0);
		/*for(int i=0;i<ah;i++) cout<<as[i]<<" ";
		cout<<endl;
		for(int i=0;i<bh;i++) cout<<bs[i]<<" ";
		cout<<endl;*/
		P ans(1e9,1e8);
		for(int i=0;i<ah;i++){
			for(int j=0;j<bh;j++){
				if(abs(as[i]-bs[j])<abs(ans.fs-ans.se)) ans=P(as[i],bs[j]);
				else if(abs(as[i]-bs[j])==abs(ans.fs-ans.se)) ans=min(ans,P(as[i],bs[j]));
			}
		}
		for(int i=0;i<lena-getlen(ans.fs);i++) printf("0");
		printf("%d ",ans.fs);
		for(int i=0;i<lenb-getlen(ans.se);i++) printf("0");
		printf("%d\n",ans.se);
	}
	return 0;
}
