#include <bits/stdc++.h>

const int MAXN = 3e5;
const int maxn = MAXN * 2;
const int maxm = MAXN;
  
using namespace std;
int ans[MAXN];
struct Suffix_Automation  
{  
    struct State  
    {  
        State *par;  
        State *go[27];  
        int val, mi, cnt, right, appear;//appear为状压记录Right集合来源  
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
    int d[maxm];  
    State* b[maxn];  
	//拓扑序后调用info来获得信息（自底向上更新）
    void topo()  
    {  
        int cnt = cur - nodePool;  
        int maxVal = 0;  
        memset(d, 0, sizeof(d));  
        for(int i = 1; i < cnt; i++) maxVal = max(maxVal, nodePool[i].val), d[nodePool[i].val]++;  
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
			ans[p->val] = std::max(ans[p->val], p->right);
        }  
        return;  
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
	sam.SAMInfo();
	for(int i = len - 1; i >= 1; i--) {
		ans[i] = std::max(ans[i], ans[i + 1]);
	}
	for(int i = 1; i <= len; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
