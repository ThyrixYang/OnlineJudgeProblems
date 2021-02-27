#include <iostream>
#include <cstring>
#include <cstdio>
const int MAXN = 5e4;
const int maxn = MAXN;
const int maxm = MAXN;
  
struct Suffix_Automation  
{  
    struct State  
    {  
        State *par;  
        State *go[27];  
        int val, mi, cnt, right, appear;//appear为状压记录Right集合来源  
		int pos;
		//val = max, mi = min, rigit(right集合大小), mi 和 right 需要递推处理
        void init(int _val = 0)  
        {  
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
    void extend(int w, int _pos)  
    {  
        State *p = last;  
        State *np = newState(p->val + 1);  
		np->pos = _pos;
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
        memset(d, 0, sizeof(d));  
        for(int i = 1; i < cnt; i++) maxVal = std::max(maxVal, nodePool[i].val), d[nodePool[i].val]++;  
        for(int i = 1; i <= maxVal; i++) d[i] += d[i - 1];  
        for(int i = 1; i < cnt; i++) b[d[nodePool[i].val]--] = &nodePool[i];  
        b[0] = root;  
    }  
    void SAMInfo()  
    {  
        State *p;  
        int cnt = cur - nodePool;  
        for(int i = cnt - 1; i > 0; i--)  
        {  
            p = b[i];  
            p->par->right += p->right;  
            p->par->appear |= p->appear;//拓扑序得到Parent树中父亲的appear  
            p->mi = p->par->val + 1;  
        }  
        return;  
    }  
	int cal(int len) {
		State *p = root;
		for(int i = 0; i < len / 2; i++) {
			for(int i = 0; i < 26; i++) {
				if(!p->go[i]) continue;
				p = p->go[i];
				break;
			}
		}
		return p->pos;
	}
};  
  
Suffix_Automation sam;  
  
char s[maxn];  
int T;
int main() {
	freopen("./in", "r", stdin);
	std::cin >> T;
	while(T--) {
		scanf("%s", s);
		sam.initSAM();
		int len = strlen(s);
		for(int i = 0; i < len; i++) s[i + len] = s[i];
		for(int i = 0; i < len * 2; i++) sam.extend(s[i] - 'a', i + 1);
		printf("%d\n", sam.cal(len * 2) - len + 1);
	}
	return 0;
}
