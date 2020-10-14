#include <bits/stdc++.h>

const int MAXN = 1e5 + 3000;
const int maxn = MAXN * 2;
const int maxm = MAXN;
  
struct Suffix_Automation {  
    struct State  {  
        State *par;  
        State *go[27];  
        int val, mi, right, appear;//appear为状压记录Right集合来源  
		long long cnt;
		//val = max, mi = min, rigit(right集合大小), mi 和 right 需要递推处理
        void init(int _val = 0)  {  
            par = 0;  
            val = _val;  
            cnt = 0;  
            mi = 0;  
            right = 0;  
            appear = 0;  
            memset(go, 0, sizeof(go));  
        }  
    };  
    State *root, *last, *cur;  
    State nodePool[maxn];  
    State *newState(int val = 0)  
    {  
        cur->init(val);  
        return cur++;  
    }  
    void initSAM()  
    {  
		//root 不是空节点
        cur = nodePool;  
        root = newState();  
        last = root;  
    }  
    void extend(int w)  
    {  
        State *p = last;  
        State *np = newState(p->val + 1);  
        np->right = 1;  
        while(p && p->go[w] == 0)  
        {  
            p->go[w] = np;  
            p = p->par;  
        }  
        if(p == 0)  
        {  
            np->par = root;  
        }  
        else  
        {  
            State *q = p->go[w];  
            if(p->val + 1 == q->val)  
            {  
                np->par = q;  
            }  
            else  
            {  
                State *nq = newState(p->val + 1);  
                memcpy(nq->go, q->go, sizeof(q->go));  
                nq->par = q->par;  
                q->par = nq;  
                np->par = nq;  
                while(p && p->go[w] == q)  
                {  
                    p->go[w] = nq;  
                    p = p->par;  
                }  
            }  
        }  
        last = np;  
    }  
	long long dfs(State *p) {
		if(p->cnt) return p->cnt;
		long long res = 0;
		for(int i = 0; i < 26; i++) {
			if(p->go[i]) res += dfs(p->go[i]);
		}
		return p->cnt = res + (p != root);
	}
	void print(long long K) {
		State *p = root, *q;
		while(K > 0) {
			for(int i = 0; i < 26; i++) {
				if(p->go[i]) {
					q = p->go[i];
					if(q->cnt < K) {
						K -= q->cnt;
					} else {
						printf("%c", i + 'a');
						K--;
						p = q;
						break;
					}
				}
			}
		}
		puts("");
	}
};  

Suffix_Automation sam; 
char s[MAXN];
int main() {
	freopen("./in", "r", stdin);
	sam.initSAM();
	scanf("%s", s);
	int len = strlen(s);
	for(int i = 0; i < len; i++) {
		sam.extend(s[i] - 'a');
	}
	sam.dfs(sam.root);
	int Q;
	scanf("%d", &Q);
	while(Q--) {
		int K;
		scanf("%d", &K);
		sam.print(K);
	}
	return 0;
}
