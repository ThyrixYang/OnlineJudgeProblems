#include <bits/stdc++.h>

using namespace std;

class Solution
{
    int prefix[20005];
    int cnt0[20005];
    int maxsuffix[20005];
    int minsuffix[20005];

public:
    int maxProduct(vector<int> &nums)
    {
        prefix[0] = 1;
        cnt0[0] = 0;
        int N = nums.size();
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == 0)
                cnt0[i + 1] = cnt0[i] + 1, prefix[i + 1] = 1;
            else
                cnt0[i + 1] = cnt0[i], prefix[i + 1] = prefix[i] * nums[i];
        }
        maxsuffix[N + 1] = 0;
        minsuffix[N + 1] = 0;
        for (int i = N; i >= 1; i--)
        {
            if (nums[i - 1] == 0)
            {
                maxsuffix[i] = 0;
                minsuffix[i] = 0;
            }
            else
            {
                maxsuffix[i] = max(maxsuffix[i + 1], prefix[i]);
                minsuffix[i] = min(minsuffix[i + 1], prefix[i]);
            }
        }
        int ans = -1e9;
        for (int i = 0; i <= N; i++)
        {
            if (prefix[i] == 0)
        }
        // for (int i = 0; i <= nums.size(); i++)
        // {
        //     for (int j = i + 1; j <= nums.size(); j++)
        //     {
        //         int c0 = cnt0[j] - cnt0[i];
        //         if (c0 == 0)
        //             ans = max(ans, prefix[j] / prefix[i]);
        //         else
        //             ans = max(ans, 0);
        //     }
        // }
        return ans;
    }
};

int main()
{

    return 0;
}