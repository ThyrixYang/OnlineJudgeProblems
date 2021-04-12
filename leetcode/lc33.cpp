#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int search(vector<int> &nums, int target)
    {

        // 二分找到旋转的位置
        int l = 0, r = nums.size();
        while (r - l > 1)
        {
            int m = (r + l) / 2;
            if (nums[m] >= nums[0])
            {
                l = m;
            }
            else
            {
                r = m;
            }
        }
        // 二分查找target，总体复杂度O(log n)
        int p1 = lower_bound(nums.begin(), nums.begin() + l + 1, target) - nums.begin();
        int p2 = lower_bound(nums.begin() + l + 1, nums.end(), target) - nums.begin();
        if (p1 < nums.size() && nums[p1] == target)
            return p1;
        if (p2 < nums.size() && nums[p2] == target)
            return p2;
        return -1;
    }
};

int main()
{

    return 0;
}