#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        vector<vector<int>> dp(505, vector<int>(505, 1e9));
        dp[0][0] = 0;
        for (int i = 0; i <= word1.length(); i++)
        {
            dp[i][0] = i;
        }
        for (int i = 0; i <= word2.length(); i++)
        {
            dp[0][i] = i;
        }
        for (int i = 0; i < word1.length(); i++)
        {
            for (int j = 0; j < word2.length(); j++)
            {
                if (word1[i] == word2[j])
                {
                    dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j]);
                }
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
                dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + 1);
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + 1);
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j + 1] + 1);
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i + 1][j] + 1);
                // dp[i+1][j+1] = min(dp[i+1][j+1], dp[i+1][j]);
                // dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j] + 1);
            }
        }
        // for (int i = 0; i <= word1.length(); i++)
        // {
        //     for (int j = 0; j <= word2.length(); j++)
        //     {
        //         cerr << dp[i][j] << " ";
        //     }
        //     cerr << endl;
        // }
        return dp[word1.length()][word2.length()];
    }
};

int main()
{
    string w1 = "";
    string w2 = "a";
    Solution sol;
    sol.minDistance(w1, w2);
    return 0;
}