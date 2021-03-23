#include <bits/stdc++.h>

using namespace std;

// 基础dp

class Solution
{
    long long dp[1005][1005];

public:
    int numDistinct(string s, string t)
    {
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int i = 1; i <= t.length(); i++)
        {
            long long sum = 0;
            for (int j = 1; j <= s.length(); j++)
            {
                sum += dp[i - 1][j - 1];
                if (s[j - 1] == t[i - 1])
                {
                    dp[i][j] += sum;
                }
            }
        }
        // for (int i = 0; i <= t.length(); i++)
        // {
        //     for (int j = 0; j <= s.length(); j++)
        //     {
        //         cout << i << " " << j << " " << dp[i][j] << endl;
        //     }
        // }
        long long ans = 0;
        for (int i = 0; i <= s.length(); i++)
        {
            ans += dp[t.length()][i];
        }
        return ans;
    }
};

int main()
{
    string s = "babgbag";
    string t = "bag";
    Solution sol;
    cout << sol.numDistinct(s, t);
    return 0;
}