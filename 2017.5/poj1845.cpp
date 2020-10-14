#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>
const int maxn=2;
const long long mod = 9901;
struct Matrix{
	long long a[maxn][maxn];
	Matrix(){memset(a,0,sizeof a);}
	Matrix operator * (Matrix b){
		Matrix ans;
		for(int i=0;i<maxn;i++)
			for(int j=0;j<maxn;j++)
				for(int k=0;k<maxn;k++)
					ans.a[i][j]=(ans.a[i][j]+a[i][k]*b.a[k][j]) % mod;
		return ans;
	}
};

Matrix qpow(Matrix a,long long p){
	Matrix ans;
	for(int i=0;i<maxn;i++) ans.a[i][i]=1;
	while(p>0){
		if(p&1) ans=ans*a;
		a=a*a;p>>=1;
	}
	return ans;
}

long long A, B;
std::map<int, int> M;
long long cal(long long p, long long d) {
	Matrix t;
	t.a[0][0] = p;
	t.a[0][1] = 1;
	t.a[1][0] = 0;
	t.a[1][1] = 1;
	t = qpow(t, d);
	return (t.a[0][0] + t.a[0][1]) % mod;
}
int main() {
	std::cin >> A >> B;
	long long d = 2;
	while(d * d <= A) {
		if(A % d == 0) {
			int c = 0;
			while(A % d == 0) {
				A /= d;
				c++;
			}
			M[d] = c;
		}
		d++;
	}
	if(A > 1) M[A] = 1;
	std::map<int, int>::iterator it;
	long long ans = 1;
	it = M.begin();
	while(it != M.end()) {
		ans = ans * cal(it -> first, it -> second * B) % mod;
		it++;
	}
	std::cout << ans << std::endl;
	return 0;
}
