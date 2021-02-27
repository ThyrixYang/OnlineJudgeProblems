//Binary Indexed Tree
#include <bits/stdc++.h>

#define lowbit(x) ((x) & ((x) ^ ((x)-1)))
#define MAXN 10000
typedef int elem_t;

struct BIT
{
    elem_t a[MAXN], c[MAXN], ret;
    int n;
    void init(int i)
    {
        memset(a, 0, sizeof(a));
        memset(c, 0, sizeof(c));
        n = i;
    }
    // update a[i] = v;
    void update(int i, elem_t v)
    {
        for (v -= a[i], a[i++] += v; i <= n; c[i - 1] += v, i += lowbit(i))
            ;
    }
    // return sum(a[0],..., a[i - 1])
    elem_t query(int i)
    {
        for (ret = 0; i; ret += c[i - 1], i ^= lowbit(i))
            ;
        return ret;
    }
};