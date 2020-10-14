#include <bits/stdc++.h>

const int MAXN = 3e5;
const int maxn = MAXN;
const int maxm = MAXN;
struct Suffix_Automation  {  
    struct State  {  
        State *par;  
        State *go[27];  
        int val, mi, cnt, right;
		int maxans, maxlen;
        void init(int _val = 0) {  
            par = 0;  
            val = _val;  
            cnt = 0;  
            mi = 0;  
            right = 0;  
			maxans = 0;
			maxlen = 0;
            memset(go, 0, sizeof(go));  

        }  
    };  
    State *root, *last, *cur;  
    State nodePool[maxn];  
    State *newState(int val = 0)  {  
        cur->init(val);  
        return cur++;  
    }  
    void initSAM()  {  
        cur = nodePool;  
        root = newState();  
        last = root;  
    }  
    void extend(int w)  {  
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
    int d[maxm];  
    State* b[maxn];  
	//拓扑序后调用info来获得信息（自底向上更新）
    void topo()  
    {  
        int cnt = cur - nodePool;  
        int maxVal = 0;  
		for(int i = 0; i < cnt; i++) nodePool[i].maxans = nodePool[i].val;
    }  
    void SAMInfo()  
    {  
        State *p;  
        int cnt = cur - nodePool;  
        for(int i = cnt - 1; i > 0; i--)  
        {  
            p = b[i];  
            p->par->right += p->right;  
            p->mi = p->par->val + 1;  
        }  
        return;  
    }  
	void upd(char *s) {
		int len = strlen(s);
		State *p = root;
		int cnt = cur - nodePool;
		int pos = 0;
		for(int i = 0; i < len; i++) {
			int c = s[i] - 'a';
			if(p->go[c]) {
				pos++;
				p = p->go[c];
				p->maxlen = std::max(p->maxlen, pos);
			} else {
				while(p && !p->go[c]) {
					p = p->par;
					if(p) p->maxlen = std::max(p->maxlen, p->val);
				}
				if(!p) {
					pos = 0;
					p = root;
				} else {
					pos = p->val + 1;
					p = p->go[c];
					p->maxlen = std::max(p->maxlen, pos);
				}
			}
		}
		for(int i = 0; i < cnt; i++) {
			nodePool[i].maxans = std::min(nodePool[i].maxans, nodePool[i].maxlen);
			nodePool[i].maxlen = 0;
		}
	}
};  
Suffix_Automation sam;  
char s[MAXN];
int main() {
	freopen("./in", "r", stdin);
	scanf("%s", s);
	int len = strlen(s);
	sam.initSAM();
	for(int i = 0; i < len; i++) sam.extend(s[i] - 'a');
	sam.topo();
	while(scanf("%s", s) != EOF) {
		sam.upd(s);
	}
	int ans = 0;
	int cnt = sam.cur - sam.nodePool;
	for(int i = 0; i < cnt; i++) {
		ans = std::max(ans, sam.nodePool[i].maxans);
	}
	printf("%d\n", ans);
	return 0;
}
