#include <bits/stdc++.h>
#include <unordered_map>
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
int A[20];
int N;
long long sum, prod;
long long p2[50], p3[50], p5[50], p7[50];
long long pp[50][50][50][50];
int ax[10][4];
long long p10[50];
long long DP(int p, int s, long long ps, int up) {
	if(s > sum) return 0;
	if(s == sum && ps > prod) return 0;
	if(s == sum && ps == prod && up == 2) return 0;
	if(s + 9 * (N - p) < sum) {
		return p10[N - p];
	}
	if(p == N) {
		if(s != sum) return s < sum;
		if(ps != prod) return ps < prod;
		return up == 0;
	}
	long long ans = 0;
	for(int i = 0; i < 10; i++) {
		int tup;
		if(up == 0) tup = 0;
		else if(up == 1) {
			if(i == A[p]) tup = 1;
			else if(i < A[p]) tup = 0;
			else tup = 2;
		} else tup = 2;
		ans += DP(p + 1, s + i, ps * (i + 1), tup);
	}
	return ans;
}
char s[20];
int main() {
	freopen("./in", "r", stdin);
	for(int i = 0; i < 10; i++) {
		int tmp = i + 1;
		while(tmp % 2 == 0) tmp /= 2, ax[i][0]++;
		while(tmp % 3 == 0) tmp /= 3, ax[i][1]++;
		while(tmp % 5 == 0) tmp /= 5, ax[i][2]++;
		while(tmp % 7 == 0) tmp /= 7, ax[i][3]++;
	}
	for(int i = 1; i < 50; i++) {
		p2[i] = p2[i - 1] * 2;
		p3[i] = p3[i - 1] * 3;
		p5[i] = p5[i - 1] * 5;
		p7[i] = p7[i - 1] * 7;
		p10[i] = p10[i - 1] * 10;
	}
	while(scanf("%s", s) != EOF) {
		N = strlen(s);
		for(int i = 0; i < N; i++) A[i] = s[i] - '0';
		sum = 0;
		prod = 1;
		for(int i = 0; i < N; i++) {
			sum += A[i];
			prod *= (A[i] + 1);
		}
		printf("%lld\n", DP(0, 0, 1, 1));
		//showtime;
	}
	
	return 0;
}
