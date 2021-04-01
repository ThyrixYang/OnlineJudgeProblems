#include <bits/stdc++.h>

using namespace std;

// 记忆化搜索

class Solution
{
    static const int MAXN = 20000;
    int dp[MAXN];
    int N;
    vector<int> _nums;
    int dfs(int s, int dep)
    {
        if (s == (1 << N) - 1)
            return 0;
        if (dp[s] != -1)
            return dp[s];
        int ans = 0;
        for (int i = 0; i < N; i++)
        {
            if ((1 << i) & s)
                continue;
            for (int j = i + 1; j < N; j++)
            {
                if ((1 << j) & s)
                    continue;
                ans = max(ans, dfs(s | (1 << i) | (1 << j), dep + 1) + dep * __gcd(_nums[i], _nums[j]));
            }
        }
        return dp[s] = ans;
    }

public:
    int maxScore(vector<int> &nums)
    {
        _nums = nums;
        memset(dp, -1, sizeof(dp));
        N = nums.size();
        return dfs(0, 1);
    }
};

int main()
{

    return 0;
}