#include <bits/stdc++.h>

using namespace std;

//经典的字符串dp

class Solution
{
    int dp[102][102][202][2];
    string _s1, _s2, _s3;

    int dfs1(int p1, int p2, int p3, int t)
    {
        if (dp[p1][p2][p3][t] != -1)
            return dp[p1][p2][p3][t];
        else if (t == 1)
        {
            dp[p1][p2][p3][t] = 0;
            for (int k = 1;; k++)
            {
                if (p2 - k < 0 || p3 - k < 0)
                    break;
                char c2 = _s2[p2 - k];
                char c3 = _s3[p3 - k];
                if (c2 == c3)
                {
                    dp[p1][p2][p3][t] |= dfs1(p1, p2 - k, p3 - k, 1 - t);
                }
                else
                {
                    break;
                }
                if (dp[p1][p2][p3][t])
                    return 1;
            }
            return 0;
        }
        else
        {
            dp[p1][p2][p3][t] = 0;
            for (int k = 1;; k++)
            {
                if (p1 - k < 0 || p3 - k < 0)
                    break;
                char c1 = _s1[p1 - k];
                char c3 = _s3[p3 - k];
                if (c1 == c3)
                {
                    dp[p1][p2][p3][t] |= dfs1(p1 - k, p2, p3 - k, 1 - t);
                }
                else
                {
                    break;
                }
                if (dp[p1][p2][p3][t])
                    return 1;
            }
            return 0;
        }
    }

public:
    bool isInterleave(string s1, string s2, string s3)
    {
        _s1 = s1;
        _s2 = s2;
        _s3 = s3;
        memset(dp, -1, sizeof(dp));
        dp[0][0][0][1] = 1;
        dp[0][0][0][0] = 1;
        int ans = dfs1(s1.length(), s2.length(), s3.length(), 0) || dfs1(s1.length(), s2.length(), s3.length(), 1);
        return ans;
    }
};

int main()
{

    return 0;
}