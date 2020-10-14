#include <bits/stdc++.h>

const int MAXN = 1e5 + 3300;
const int SZ = 320;
int n;
int a[MAXN];
struct Node {
	int val;
	Node *next, *pre;
	Node() {
		next = pre = NULL;
		val = 0;
	}
}N[MAXN * 2];
int nh = 0;
struct List {
	Node *begin, *end;
	List() {
		begin = &N[nh++];
		end = &N[nh++];
		begin->next = end;
		end->pre = begin;
	}
	Node *back(){return end->pre;}
	void insert(Node *l, Node *r, Node *a) {
		l->next = a, r->pre = a, a->pre = l, a->next = r;
	}
	Node *kth(int k) {
		Node *n = begin;
		for(int i = 0; i < k; i++) n = n->next;
		return n;
	}
	void insert(int p, int x) {
		Node *a = &N[nh++];
		a->val = x;
		Node *n = kth(p), *pp = n->pre;
		insert(pp, n, a);
	}
	void insert(int p, Node *x) {
		Node *n = kth(p);
		Node *pp = n->pre;
		insert(pp, n, x);
	}
	void append(int x) {
		Node *a = &N[nh++];
		a->val = x;
		Node *p = end->pre;
		insert(p, end, a);
	}
	void erase(Node *n) {
		n->pre->next = n->next;
		n->next->pre = n->pre;
	}
	void out() {
		Node *x = begin;
		puts("out");
		while(x != end) {
			printf("%d ", x->val);
			x = x->next;
		}
		puts("\nout");
	}
}L[350];
int cnt[MAXN][350];
int lastAns = 0;
void decode(int &x) {
	x = (x + lastAns - 1) % n + 1;
}
int main() {
	freopen("./in", "r", stdin);
	std::cin >> n;
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	for(int i = 0; i < n; i++) {
		L[i / SZ].append(a[i]);
		cnt[a[i]][i / SZ]++;
	}
	int q;
	scanf("%d", &q);
	while(q--) {
		int t;
		scanf("%d", &t);
		if(t == 1) {
			int l, r;
			scanf("%d%d", &l, &r);
			decode(l);decode(r);
			l--, r--;
			if(l == r) continue;
			if(l > r) std::swap(l, r);
			if(l / SZ == r / SZ) {
				Node *rv = L[l / SZ].kth(r % SZ + 1);
				L[l / SZ].erase(rv);
				L[l / SZ].insert(l % SZ + 1, rv);
			}else {
				Node *rv = L[r / SZ].kth(r % SZ + 1);
				L[r / SZ].erase(rv);
				cnt[rv->val][r / SZ]--;
				cnt[rv->val][l / SZ]++;
				L[l / SZ].insert(l % SZ + 1, rv);
				for(int i = l / SZ; i < r / SZ; i++) {
					Node *x = L[i].back();
					cnt[x->val][i]--;
					cnt[x->val][i + 1]++;
					L[i].erase(x);
					L[i + 1].insert(1, x);
				}
			}
		}else{
			int l, r, k;
			scanf("%d%d%d", &l, &r, &k);
			decode(l);decode(r);decode(k);
			if(l > r) std::swap(l, r);
			l--, r--;
			int ans = 0;
			if(l / SZ == r / SZ) {
				Node *lv = L[l / SZ].kth(l % SZ + 1);
				for(int i = 0; i < r - l + 1; i++) {
					ans += (lv->val == k);
					lv = lv->next;
				}
				printf("%d\n", ans);
				lastAns = ans;
				continue;
			}
			for(int i = l / SZ + 1; i < r / SZ; i++) {
				ans += cnt[k][i];
			}
			Node *x = L[l / SZ].kth(l % SZ + 1);
			while(x != L[l / SZ].end) {
				ans += (x->val == k);
				x = x->next;
			}
			x = L[r / SZ].kth(r % SZ + 1);
			while(x != L[r / SZ].begin) {
				ans += (x->val == k);
				x = x->pre;
			}
			printf("%d\n",ans);
			lastAns = ans;
		}
	}
	return 0;
}
