#include<bits/stdc++.h>

using namespace std;

const int MAXN=100;
const double EPS=1e-8;
int sgn(double x){
	if(fabs(x)<EPS) return 0;
	if(x<0) return -1;
	return 1;
}
struct Simplex(){
	//矩阵A的第0行是变量标号，第二行是目标函数，后面若干行是约束条件.
	double A[MAXN][MAXN];
	int n,m;//矩阵为n行m列
	void swapCol(int x,int y){
		for(int i=0;i<n;i++) swap(A[i][x],A[i][y]);
	}
	void swapLine(int x,int y){
		for(int i=0;i<m;i++) swap(A[x][i],A[y][i]);
	}
	bool Gauss(){
		int maxr=1,col=0;
		for(;col<Var;col++){
			for(int i=maxr;i<n;i++){
				if(sgn(A[i][col])!=0){
					if(i!=maxr) swapLine(maxr,i);
					break;
				}
			}
			if(sgn(A[i][col])==0) continue;
			
		}
	}
};
int main(){
	return 0;
}
