#include <bits/stdc++.h>

using namespace std;

const int tol = 1000000;
int T = 120;
int N = 1000;
vector<int> GeneratorBad(int n) {
	vector<int> res(n);
	for(int i = 0; i < n; i++) res[i] = i;
	for(int i = 0; i < n; i++) {
		int j = rand() % n;
		swap(res[i], res[j]);
	}
	return res;
}
vector<int> GeneratorGood(int n) {
	vector<int> res(n);
	for(int i = 0; i < n; i++) res[i] = i;
	for(int i = 0; i < n; i++) {
		int j = rand() % (n - i);
		swap(res[i], res[j + i]);
	}
	return res;
}
vector<vector<int> > CalMat(int n) {
	vector<vector<int> > mat(n, vector<int>(n));
	for(int rep = 0; rep < tol; rep++) {
		vector<int> res = GeneratorBad(n);
		for(int i = 0; i < n; i++) {
			mat[i][res[i]]++;
		}
	}
	return mat;
}
void Write(const vector<vector<int> > &mat) {
	ofstream out("../Data/gcj2014r1ac/mat");
	for(int i = 0; i < (int) mat.size(); i++) {
		for(int j = 0; j < (int) mat[i].size(); j++) {
			out << mat[i][j] << " ";
		}
		out << endl;
	}
	out.close();
}
vector<vector<int> > Read(int n) {
	ifstream in("../Data/gcj2014r1ac/mat");
	vector<vector<int> > mat(n, vector<int>(n));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			in >> mat[i][j];
		}
	}
	in.close();
	return mat;
}
vector<vector<int> > pm;
int Test(const vector<int> &s) {
	int n = s.size();
	long double lpg = n * log(1.0 / n);
	long double lpb = 0;
	for(int i = 0; i < n; i++) {
		lpb += log(pm[i][s[i]] * 1.0 / tol);
	}
	long double pg = 1 / (1 + exp(lpb - lpg));
	if(pg > 0.5) return 1;
	else return 0;
}
int main() {
	srand(time(0));
	//vector<vector<int> > mat = CalMat(1000);
	//Write(mat);
	pm = Read(1000);
	/*for(int i = 0; i < 100; i++) {
		vector<int> tmp = GeneratorGood(1000);
		if(!Test(tmp)) puts("NO");
		else puts("YES");
	}*/
	/*
	freopen("../Data/gcj2014r1ac/in", "r", stdin);
	freopen("../Data/gcj2014r1ac/out", "w", stdout);
	cin >> T;
	for(int cas = 1; cas <= T; cas++) {
		cin >> N;
		vector<int> tmp(N);
		printf("Case #%d: ", cas);
		for(int i = 0; i < N; i++) cin >> tmp[i];
		if(Test(tmp)) puts("GOOD");
		else puts("BAD");
	}
	*/
	T = 100000;
	int correct = 0;
	for(int cas = 0; cas < T; cas++) {
		vector<int> tmp;
		if(cas & 1) tmp = GeneratorGood(1000);
		else tmp = GeneratorBad(1000);
		if(Test(tmp) == (1 & cas)) correct++;
	}
	printf("%.5f\n", correct / (double) T);
	return 0;
}
