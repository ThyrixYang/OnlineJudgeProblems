#include <bits/stdc++.h>

const double EPS = 1e-8;
double p;

const int MAXN = 400;
double a[MAXN][MAXN];
int id[30][30];
int f = 0;
void Gauss() {
	for(int i = 0; i < f; i++) {
		int k = i;
		double x = a[i][i];
		if(std::fabs(x) < EPS) continue;
		for(int j = i; j < f + 1; j++) {
			std::swap(a[i][j], a[k][j]);
			a[i][j] = a[i][j] / x;
		}
		for(int j = 0; j < f; j++) {
			if(j == i || std::fabs(a[j][i]) < EPS) continue;
			x = a[j][i];
			for(int k = i; k < f + 1; k++) {
				a[j][k] -= x * a[i][k];
			}
		}
	}
}
int main() {
	freopen("./in", "r", stdin);
	for(int i = 0; i <= 19; i++) {
		for(int j = 0; j <= i; j++) {
			id[i][j] = f++;
		}
	}
	while(scanf("%lf", &p) != EOF) {
		for(int i = 0; i < f; i++)
			for(int j = 0; j < f + 1; j++) a[i][j] = 0;
		for(int i = 0; i <= 19; i++) {
			for(int j = 0; j <= i; j++) {
				int r = id[i][j];
				a[r][r] = 1;
				if(i == j) {
					if(i + 1 < 20) a[r][id[i + 1][j]] += -p;
					if(j - 2 >= 0) a[r][id[i][j - 2]] += (p - 1);
					else a[r][id[i][0]] += (p - 1);
				} else {
					a[r][id[i][j + 1]] += -p;
					if(j - 2 >= 0) a[r][id[i][j - 2]] += p - 1;
					else a[r][id[i][0]] += p - 1;
				}
				a[r][f] = 1;
			}
		}
		Gauss();
		printf("%.7f\n",a[0][f]);
	}
	/*
	f = 4;
	a[0][0] = 2, a[0][1] = -1;
	a[1][1] = 1, a[1][2] = -1;
	a[2][2] = 1;
	a[0][3] = a[1][3] = a[2][3] = 1;
	Gauss();
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 4; j++) {
			printf("%.2f ", a[i][j]);
		}
		puts("");
	}*/
	return 0;
}
