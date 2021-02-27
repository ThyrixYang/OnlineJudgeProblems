#include<bits/stdc++.h>

using namespace std;

const double EPS=1e-8;
const int MAXR=100;
const int MAXC=100;
double sgn(double x){
	if(fabs(x)<EPS) return 0;
	if(x>0) return 1;
	return -1;
}
struct Matrix{
	double a[MAXR][MAXC];
	void set(int x,int y,double val){
		a[x][y]=val;
	}
};
struct Simplex{
	int Var,Equ,last;//变量的数目和等式的数量,最后一列
	int tab[MAXC];//矩阵中系数对应的变元编号长度n。
	Matrix A;//A是系数矩阵,调用的时候，后面是n*n的单位矩阵,为basis
	//A矩阵的第0行为目标函数。
	Simplex(Matrix a,int V,int E){
		Var=V,Equ=E;
		A=a;
		for(int i=0;i<=Var+Equ;i++) tab[i]=i;
		last=Var+Equ;
	}
	void outPut(){
		for(int i=Var;i<last;i++){
			cout<<tab[i]<<" "<<-A.a[i-Var+1][last]<<endl;
		}
	}
	void swapCol(int x,int y){
		swap(tab[x],tab[y]);
		for(int i=0;i<=Equ;i++) swap(A.a[i][x],A.a[i][y]);
	}
	double simplex(){
		for(;;){
			bool f=0;
			int v=0,u;
			for(int i=0;i<Var;i++){
				if(sgn(A.a[0][i])>0){
					double lim=1e30;
					u=-1;
					for(int j=1;j<=Equ;j++){
						if(sgn(A.a[j][i])>0&&sgn(A.a[j][last])<0){
							double tmp=-A.a[j][last]/A.a[j][i];
							if(tmp<lim){
								lim=tmp;
								u=j;
							}
						}
					}
					if(sgn(lim)>0&&u!=-1){
						f=1;
						v=i;
						break;
					}
				}
			}
			if(!f) break;
			double tmp=A.a[u][v];
			for(int i=0;i<=last;i++) A.a[u][i]/=tmp;
			for(int i=0;i<=Equ;i++){
				if(i==u) continue;
				tmp=A.a[i][v];
				for(int j=0;j<=last;j++) A.a[i][j]-=A.a[u][j]*tmp;
			}
			swapCol(v,Var+u-1);
		}
		return A.a[0][last];
	}
};
bool judge(Matrix a,int Var,int Equ){
	
}
int main(){
	freopen("./in","r",stdin);
	Matrix A;
	A.set(0,0,-3),A.set(0,1,1),A.set(0,2,0),A.set(0,3,0),A.set(0,4,20);
	A.set(1,0,-3),A.set(1,1,3),A.set(1,2,1),A.set(1,3,0),A.set(1,4,-6);
	A.set(2,0,-8),A.set(2,1,4),A.set(2,2,0),A.set(2,3,1),A.set(2,4,-4);
	Simplex solver(A,2,2);
	cout<<solver.simplex()<<endl;
	solver.outPut();
	return 0;
}
/*
 *  -3*x0 + 1*x1 + 0*x2 + 0*x3 + 20 = z;
 *  -3*x0 + 3*x1 + 1*x2        - 6  = 0;
 *  -8*x0 + 4*x1 +      + 1*x3 - 4  = 0;
 *  最优解为z=21;
 */
