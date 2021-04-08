#include <bits/stdc++.h>

using namespace std;

// 动态规划

class Solution
{
public:
    int maximumScore(vector<int> &nums, vector<int> &multipliers)
    {
        int m = multipliers.size();
        int n = nums.size();
        vector<int> dpx = {0};
        for (int i = 1; i <= m; i++)
        {
            vector<int> dpy(i + 1, -1e9);
            for (int j = 0; j <= i; j++)
            {
                if (j < i)
                    dpy[j] = max(dpy[j], dpx[j] + nums[n - (i - j)] * multipliers[i - 1]);
                if (j > 0)
                    dpy[j] = max(dpy[j], dpx[j - 1] + nums[j - 1] * multipliers[i - 1]);
            }
            dpx = dpy;
        }
        int ans = -1e9;
        for (auto v : dpx)
        {
            ans = max(ans, v);
        }
        return ans;
    }
};

int main()
{

    return 0;
}