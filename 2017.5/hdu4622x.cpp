    #include <iostream>  
    #include <string.h>  
    #include <algorithm>  
    #include <stdio.h>  
      
    using namespace std;  
    const int N=5010;  
      
    struct State  
    {  
        State *pre,*go[26];  
        int step;  
        void clear()  
        {  
            pre=0;  
            step=0;  
            memset(go,0,sizeof(go));  
        }  
        int calc()  
        {  
            if(pre==0) return 0;  
            return step-pre->step;  
        }  
    }*root,*last;  
      
    State statePool[N*2],*cur;  
      
    void init()  
    {  
        cur=statePool;  
        root=last=cur++;  
        root->clear();  
    }  
      
    int tot;  
    void Insert(int w)  
    {  
        State *p=last;  
        State *np=cur++;  
        np->clear();  
        np->step=p->step+1;  
        while(p&&!p->go[w])  
            p->go[w]=np,p=p->pre;  
        if(p==0)  
        {  
            np->pre=root;  
            tot+=np->calc();  
        }  
        else  
        {  
            State *q=p->go[w];  
            if(p->step+1==q->step)  
            {  
                np->pre=q;  
                tot+=np->calc();  
            }  
            else  
            {  
                State *nq=cur++;  
                nq->clear();  
                memcpy(nq->go,q->go,sizeof(q->go));  
                tot-=p->calc()+q->calc();  
                nq->step=p->step+1;  
                nq->pre=q->pre;  
                q->pre=nq;  
                np->pre=nq;  
                tot+=p->calc()+q->calc()+np->calc()+nq->calc();  
                while(p&&p->go[w]==q)  
                    p->go[w]=nq, p=p->pre;  
            }  
        }  
        last=np;  
		printf("%d %d\n", last->step, last->pre->step);
    }  
      
    int ans[N][N];  
    char s[N];  
      
    void work()  
    {  
        scanf("%s",s);  
        int n=strlen(s);  
        for(int i=0;i<n;++i)  
        {  
            init();  
            tot=0;  
            for(int j=i;j<n;++j)  
            {  
                Insert(s[j]-'a');  
                ans[i][j]=tot;  
            }  
        }  
        int nQ;  
        scanf("%d", &nQ);  
        while (nQ--)  
        {  
            int l, r;  
            scanf("%d%d", &l, &r);  
            --l,--r;  
            printf("%d\n", ans[l][r]);  
        }  
    }  
      
    int main()  
    {  
		freopen("./in", "r", stdin);
        int T;  
        cin>>T;  
        while(T--)  
            work();  
        return 0;  
    }  
