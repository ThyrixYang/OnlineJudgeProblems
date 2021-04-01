#include <bits/stdc++.h>

using namespace std;

class Solution
{
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

    struct Discretize
    {
        vector<int> value;
        int back;
        void add(int v)
        {
            value.push_back(v);
        }
        void discretize()
        {
            sort(value.begin(), value.end());
            back = unique(value.begin(), value.end()) - value.begin();
        }
        int get_id(int v)
        {
            return lower_bound(value.begin(), value.begin() + back, v) - value.begin();
        }
        int get_size()
        {
            return back;
        }
    };
    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        if (a[1] != b[1])
            return a[1] < b[1];
        return a[0] < b[0];
    }

public:
    int maxValue(vector<vector<int>> &events, int k)
    {
        sort(events.begin(), events.end(), cmp);
        SegmentTree dp[k + 1];
        Discretize dis;
        int ans = 0;
        for (int i = 0; i < events.size(); i++)
        {
            dis.add(events[i][0]);
            dis.add(events[i][1]);
        }
        dis.discretize();
        for (int i = 0; i <= k; i++)
            dp[i].init(dis.get_size() + 5, 0);
        for (int i = 0; i < events.size(); i++)
        {
            int s = dis.get_id(events[i][0]);
            int t = dis.get_id(events[i][1]);
            // cerr << "---------" << endl;
            // cerr << s << " " << t << endl;
            for (int j = 1; j <= k; j++)
            {
                // cerr << "***********" << endl;
                int res = dp[j - 1].query(0, s);
                ans = max(ans, res + events[i][2]);
                // cerr << i << " " << j << " " << res << " " << events[i][2] << endl;
                dp[j].update(t, res + events[i][2]);
            }
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> a;
    a.push_back(vector<int>{1, 2, 4});
    a.push_back(vector<int>{3, 4, 3});
    a.push_back(vector<int>{2, 3, 1});
    vector<vector<int>> b;
    b.push_back(vector<int>{1, 1, 1});
    b.push_back(vector<int>{2, 2, 2});
    b.push_back(vector<int>{3, 3, 3});
    b.push_back(vector<int>{4, 4, 4});
    int ans = sol.maxValue(b, 3);
    cerr << ans << endl;
    return 0;
}