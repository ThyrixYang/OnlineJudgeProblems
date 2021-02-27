#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e6;
typedef pair<int, int> P;
int N, K;
P seg[MAXN];
int dic[MAXN];
int dh;
int val[MAXN];
#define chl ((o << 1))
#define chr ((o << 1) | 1)
#define mi ((r + l) >> 1)
#define idx(x) (lower_bound(dic, dic + dh, x) - dic)
void add(int o, int p, int l, int r, int x) {
	if(r - l <= 1) {
		val[o] += x;
		return;
	}
	if(p < mi) add(chl, p, l, mi, x);
	else add(chr, p, mi, r, x);
	val[o] = val[chl] + val[chr];
}
int findPos(int o, int k, int l, int r) {
	if(r - l <= 1) return l;
	if(val[chr] >= k) return findPos(chr, k, mi, r);
	else return findPos(chl, k - val[chr], l, mi);
}
P out[MAXN];
int L[MAXN], R[MAXN];
int main() {
	freopen("./Data/stdin", "r", stdin);
	cin >> N >> K;
	for(int i = 0; i < N; i++) {
		scanf("%d%d", &seg[i].first, &seg[i].second);
		dic[dh++] = seg[i].second;
		L[i] = seg[i].first;
		R[i] = seg[i].second;
	}
	dic[dh++] = -2e9;
	sort(dic, dic + N);
	dh = unique(dic, dic + N) - dic;
	sort(seg, seg + N);
	int ans = 0;
	int p = 0;
	for(int i = 0; i < N; i++) {
		add(1, idx(seg[i].second), 0, dh, 1);
		int res = findPos(1, K, 0, dh);
		if(dic[res] < seg[i].first || i < K - 1) continue;
		int tmp = dic[res] - seg[i].first + 1;
		if(tmp > ans) {
			ans = tmp;
			p = i;
		}
	}
	cout << ans << endl;
	if(ans == 0) {
		for(int i = 0; i < K; i++) {
			printf("%d ", i + 1);
		}
		return 0;
	}
	int oh = 0;
	for(int i = 0; i < N; i++) {
		if(L[i] <= seg[p].first) {
			out[oh++] = P(R[i], i);
		}
	}
	sort(out, out + oh, greater<P>() );
	for(int i = 0; i < K; i++) {
		printf("%d ", out[i].second + 1);
	}
	return 0;
}
