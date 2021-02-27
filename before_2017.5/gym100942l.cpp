#include <bits/stdc++.h>

using namespace std;
#define pb push_back

int sgn(int x){
	if(x==0) return 0;
	if(x<0) return -1;
	return 1;
}
struct op{
	int t,a,b,c;
	op(int t,int a=0,int b=0,int c=0):t(t),a(a),b(b),c(c){}
};
int a,b;
int c,d;
vector<op> ans;
bool flag=0;
void out(){
	cout<<ans.size()<<endl;
	for(int i=0;i<ans.size();i++){
		if(flag){
			if(ans[i].t==1) printf("%d %d %d\n",1,ans[i].b,ans[i].a);
			else if(ans[i].t==2) printf("%d %d %d\n",2,ans[i].b,ans[i].a);
			else printf("%d %d %d %d %d\n",3,ans[i].c,ans[i].b,ans[i].b,ans[i].a);
		}else{
			if(ans[i].t==1) printf("%d %d %d\n",1,ans[i].a,ans[i].b);
			else if(ans[i].t==2) printf("%d %d %d\n",2,ans[i].a,ans[i].b);
			else printf("%d %d %d %d %d\n",3,ans[i].a,ans[i].b,ans[i].b,ans[i].c);
		}
	}
}
int main(){
	//////freopen("/home/cwind/vimFile/in","r",stdin);
	cin>>a>>b>>c>>d;
	if(sgn(a-b)!=sgn(c-d)){
		puts("0");
		return 0;
	}
	if(a==b){
		for(;;){
			if(a==1) break;
			if(a&1){
				ans.pb(op(1,a,a));
				a++,b++;
				continue;
			}
			ans.pb(op(2,a,b));
			a>>=1;b>>=1;
		}
		if(a>c){
			puts("0");
			return 0;
		}
		for(int i=0;i<c-a;i++)
			ans.pb(op(1,a+i,a+i));
		out();
		return 0;
	}
	if(a>b){
		swap(a,b);swap(c,d);
		flag=1;
	}
	for(;;){
		if(a%2!=b%2){
			if(a==1) break;
			if(a&1){
				ans.pb(op(1,a,b));
				a++,b++;
				continue;
			}
			for(int i=0;i<b-a;i++)
				ans.pb(op(1,a+i,b+i));
			ans.pb(op(3,a,b,2*b-a));
			b+=b-a;
		}else if(a%2==0){
			ans.pb(op(2,a,b));
			a>>=1;
			b>>=1;
		}else{
			ans.pb(op(1,a,b));
			a++,b++;
		}
	}
	if(b-a>d-c||(d-c)%(b-a)!=0||a>c){
		puts("0");
		return 0;
	}
	for(int i=0;i<c-a;i++)
		ans.pb(op(1,a+i,b+i));
	int D=b-a;
	for(int i=1;i<(d-c)/(b-a);i++){
		for(int j=0;j<D;j++) ans.pb(op(1,c+(i-1)*D+j,c+i*D+j));
		ans.pb(op(3,c,c+i*D,c+(i+1)*D));
	}
	out();
	return 0;
}
