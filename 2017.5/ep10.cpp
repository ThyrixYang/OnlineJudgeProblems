#include <bits/stdc++.h>
#include <unordered_map>
#define mp std::make_pair

const int maxn = 1e6+200;
std::unordered_map<long long , long long > S;
bool np[maxn];
int pri[maxn];
long long sum[maxn];
void getPrime() {
	for(int i = 2; i < maxn; i++ ) {
		if(!np[i]) pri[++pri[0]] = i;
		for(int j = 1; j <= pri[0]; j++) {
			int p = pri[j];
			if(p * i >= maxn) break;
			np[p * i] = 1;
			if( i % p == 0) break;
		}
	}
	for(int i = 2; i < maxn; i++) {
		sum[i] = sum[i - 1];
		if(!np[i]) sum[i] += i;
	}
}
long long cal(long long v, long long p){
	if(p <= 1) return (v + 2) * (v - 1) / 2;
	p = std::min(p,(long long)sqrt(v) + 1);
	long long id = v * 1e9 + p;
	if(S.find(id) != S.end()) return S[id];	
	long long ans = cal(v, p - 1);
	if(np[p]) return S[id] = ans;
	if(p * p > v) return S[id] = ans;
	ans -= p * (cal(v / p, p - 1) - sum[p - 1]);
	return S[id] = ans;
}
int main() {
	getPrime();
	std::cout << cal(1e9, sqrt(1e9)) << std::endl;
	return 0;
}
