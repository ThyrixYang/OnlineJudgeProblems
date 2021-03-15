#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        int ans1 = 0, ans2 = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[i] + nums[j] == target)
                {
                    ans1 = i;
                    ans2 = j;
                }
            }
        }
        return vector<int>{ans1, ans2};
    }
};

int main()
{

    return 0;
}