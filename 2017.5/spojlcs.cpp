#include <bits/stdc++.h>

const double eps(1e-8);  
const int MAXN = 6e5;
const int maxn = MAXN * 2;
const int maxm = MAXN;
using namespace std;
typedef long long lint;  
struct Suffix_Automation  
{  
    struct State  
    {  
        State *par;  
        State *go[27];  
        int val, mi, cnt, right, appear;//appear为状压记录Right集合来源  
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
        cur = nodePool;  
        root = newState();  
        last = root;  
    }  
    void extend(int w, int belong)  
    {  
        State *p = last;  
        State *np = newState(p->val + 1);  
        np->right = 1;  
        np->appear |= (1 << belong);  
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
    int SAMInfo()  
    {  
		int ans = 0;
        State *p;  
        int cnt = cur - nodePool;  
        for(int i = cnt - 1; i > 0; i--)  
        {  
            p = b[i];  
            p->par->right += p->right;  
            p->par->appear |= p->appear;//拓扑序得到Parent树中父亲的appear  
            p->mi = p->par->val + 1;  
			if(p->appear == 3) ans = std::max(ans, p->val);
        }  
        return ans;
    }  
}sam;
char A[MAXN], B[MAXN];
int main() {
	freopen("./in", "r", stdin);
	scanf("%s", A);
	scanf("%s", B);
	sam.initSAM();
	int lena = strlen(A);
	int lenb = strlen(B);
	for(int i = 0; i < lena; i++) sam.extend(A[i] - 'a', 0);
	sam.extend('z' - 'a' + 1, 0);
	for(int i = 0; i < lenb; i++) sam.extend(B[i] - 'a', 1);
	sam.topo();
	int ans = sam.SAMInfo();
	printf("%d\n", ans);
	return 0;
}
