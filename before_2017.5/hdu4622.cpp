#include <bits/stdc++.h>

int cnt;
const int MAXN = 4000;
struct Node {
    Node *pre, *son[26];
    int len;
	int cal(){return len - pre->len;}
	void clear() {
		pre = 0;
		memset(son, 0, sizeof son);
	}
}*root, *tail, que[MAXN];
int tot;
void add(int c) {
    Node *p = tail, *np = &que[tot++];
	np->clear();
    np->len = p->len + 1;
    while(p && !p->son[c]) p->son[c] = np, p = p->pre;
    if(!p) np->pre = root, cnt += np->cal();
    else {
        Node *q = p->son[c];
        if(p->len + 1 == q->len) np->pre = q, cnt += np->cal();
        else {
            Node *nq = &que[tot++];
            *nq = *q;
			cnt -= q->cal();
            nq->len = p->len + 1;
            np->pre = q->pre = nq;
			cnt += nq->cal() + np->cal() + q->cal();
            while(p && p->son[c] == q) p->son[c] = nq, p = p->pre;
        }
    }
    tail = np;
	printf("%d %d\n", tail->len, tail->pre->len);
}
void clear() {
	tot = 0;
	root = tail = &que[tot++];
}
int mat[MAXN][MAXN];
int T;
char s[MAXN];
int len, m;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		scanf("%s", s);
		len = strlen(s);
		for(int i = 0; i < len; i++) {
			clear();
			cnt = 0;
			for(int j = i ; j < len; j++) {
				add(s[j] - 'a');
				mat[i][j] = cnt;
			}
		}
		scanf("%d", &m);
		while(m--) {
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%d\n", mat[l - 1][r - 1]);
		}
	}
	return 0;
}
