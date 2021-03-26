#include <bits/stdc++.h>

using namespace std;

//基础区间dp

class Solution
{
public:
    int maxCoins(vector<int> &nums)
    {
        vector<int> A;
        A.push_back(1);
        for (int i = 0; i < nums.size(); i++)
        {
            A.push_back(nums[i]);
        }
        A.push_back(1);
        int N = A.size();
        vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));
        for (int k = 2; k < N; k++)
        {
            for (int i = 0; i < N - 1; i++)
            {
                int j = i + k;
                if (j >= N)
                    break;
                for (int m = i + 1; m < j; m++)
                {
                    dp[i][j] = max(dp[i][j], A[i] * A[j] * A[m] + dp[i][m] + dp[m][j]);
                }
            }
        }
        return dp[0][N - 1];
    }
};

int main()
{

    return 0;
}