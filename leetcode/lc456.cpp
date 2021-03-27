#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    bool find132pattern(vector<int> &nums)
    {
        vector<pair<int, int>> A;
        A.push_back(make_pair(nums[0], nums[0]));
        for (int i = 1; i < nums.size(); i++)
        {
            int v = nums[i];
            if (v < A.back().first)
            {
                A.push_back(make_pair(v, v));
            }
            else if (v == A.back().first)
            {
                continue;
            }
            else
            {
                if (v < A.back().second)
                {
                    return true;
                }
                else if (v == A.back().second)
                {
                    continue;
                }
                else
                {
                    int m = A.back().first;
                    while (A.size() > 0 && v >= A.back().second)
                    {
                        A.pop_back();
                    }
                    if (A.size() > 0 && A.back().first < v)
                        return true;
                    A.push_back(make_pair(m, v));
                }
            }
        }
        return false;
    }
};

int main()
{
    Solution sol;
    vector<int> a = {1, 2, 3, 4};
    vector<int> b = {3, 1, 4, 2};
    vector<int> c = {-1, 3, 2, 0};
    int res = sol.find132pattern(c);
    cerr << res << endl;
    return 0;
}