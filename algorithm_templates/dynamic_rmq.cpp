#include <bits/stdc++.h>

using namespace std;

struct SegmentTree
{
    // 区间最值，动态更新
    vector<int> value;
    int N;
    static inline int chl(int o)
    {
        return o << 1;
    }
    static inline int chr(int o)
    {
        return (o << 1) | 1;
    }
    void init(int n, int init_value)
    {
        value = vector<int>(n * 4, init_value);
        N = n;
    }
    int query(int l, int r)
    {
        return _query(1, 0, N, l, r);
    }
    int _query(int o, int l, int r, int ql, int qr)
    {
        // cerr << o << " " << l << " " << r << " " << ql << " " << qr << " " << value[o] << endl;
        if (r <= qr && l >= ql)
            return value[o];
        if (r <= ql || l >= qr)
            return 0;
        int m = (l + r) / 2;
        int value_l = _query(chl(o), l, m, ql, qr);
        int value_r = _query(chr(o), m, r, ql, qr);
        return max(value_l, value_r);
    }
    void _update(int o, int l, int r, int p, int v)
    {
        if (r - l <= 1)
        {
            value[o] = max(value[o], v);
            return;
        }
        int m = (r + l) / 2;
        if (p < m)
            _update(chl(o), l, m, p, v);
        else
            _update(chr(o), m, r, p, v);
        value[o] = max(value[chl(o)], value[chr(o)]);
    }
    void update(int p, int v)
    {
        _update(1, 0, N, p, v);
    }
};