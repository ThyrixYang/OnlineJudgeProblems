#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;

#define Maxn 1000000
#define ll long long
bool c[Maxn];
int prime[Maxn];
int tot;
void Euler(int n){ //筛出[1,n]之间的素数
    //memset(c,0,sizeof c);
    tot=0;
    for(int i=2;i<=n;i++){
        if(!c[i]) prime[tot++]=i;
        for(int j=0;j<tot;j++){
            if(i*prime[j]>n) break;
            c[i*prime[j]]=true;
            if(i%prime[j]==0) break; //保证被最小质因数筛除
        }
    }
}
int pi[Maxn]; //pi[i]:1~i的素数个数
const int Maxm=50001; //大于这个值即可
const int Maxd=0; //Maxm的素因子个数
const int num=50;
int f[num][Maxm+1]; //小规模phi(n,m)
int pre[Maxd+1];
void init(){ //预处理f
    Euler(Maxn-1); //欧拉筛
    for(int i=2;i<Maxn;i++){
        pi[i]=pi[i-1];
        if(!c[i]) pi[i]++;
    }
    pre[0]=1;
    for(int i=1;i<=Maxd;i++) pre[i]=pre[i-1]*prime[i-1];
    for(int i=0;i<num;i++)
        for(int j=0;j<=Maxm;j++)
            if(!i) f[i][j]=j;
            else f[i][j]=f[i-1][j]-f[i-1][j/prime[i-1]];
}
ll phi(int n,ll m){ //大规模phi(n,m)
    if(!n) return m;
    if(n<=Maxd) return f[n][m%pre[n]]+(m/pre[n])*f[n][pre[n]];
    if(m<=prime[n-1]) return 1;
    if(m<=prime[n-1]*prime[n-1]&&m<Maxn) return pi[m]-n+1;
    if(m<=Maxm&&n<num) return f[n][m];
    return phi(n-1,m)-phi(n-1,m/prime[n-1]);
}
ll lehmer(ll m){ //计算pi(m)
    if(m<Maxn) return pi[m];
    int q2=sqrt(m+0.5),q3=cbrt(m+0.5);
    int n=pi[q3];
    ll res=phi(n,m)+n-1;
    for(int i=n;prime[i]<=q2;i++) //prime[tot-1] > sqrt(1e11)
        res=res-lehmer(m/prime[i])+lehmer(prime[i])-1;
    return res;
}
int main() {
    init();
	long long n;
	while(std::cin >> n) {
		std::cout << lehmer(n) << std::endl;
	}
	return 0;
}
