#include <bits/stdc++.h>

using namespace std;

class Solution
{
    int in_stack[1005];
    vector<int> G;

public:
    int reinitializePermutation(int n)
    {
        G = vector<int>(n, -1);
        for (int i = 0; i < n; i++)
        {
            if (i % 2 == 0)
            {
                G[i / 2] = i;
            }
            else
            {
                G[n / 2 + (i - 1) / 2] = i;
            }
        }
        memset(in_stack, 0, sizeof(in_stack));
        long long ans = 1;
        // cerr << "ss" << endl;
        // cerr << n << endl;
        for (int i = 0; i < n; i++)
        {
            if (!in_stack[i])
            {
                long long cnt = 1;
                int v = G[i];
                in_stack[i] = 1;
                while (v != i)
                {
                    in_stack[v] = 1;
                    cnt++;
                    v = G[v];
                }
                long long g = __gcd(ans, cnt);
                ans = ans * cnt / g;
                //cerr << cnt << endl;
            }
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    int ans = sol.reinitializePermutation(6);
    cerr << ans << endl;
    return 0;
}